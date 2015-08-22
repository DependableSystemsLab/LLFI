#! /usr/bin/env python3

"""
(%prog)s takes a .fidl and generates ... 

Usage: %(prog)s [OPTIONS] <fidl .yaml>

List of options:
-r:    removes the specified injector by '<FMode>(<FClass>)' or by the index shown in -l
-l:    lists all active passes/injector
-h:    shows help

Everytime the contents of .fidl file is changed, this script should be run to create new passes and injectors
It is assumed that the script is executed in the <llfisrc>/tools/FIDL/ directory

Class and mode pair must be unique!

"""

import sys, os
import shutil, errno
import subprocess
import yaml

################################################################################

script_path = os.path.realpath(os.path.dirname(__file__))

### PHIL @ July 12
llfiroot = os.path.dirname(os.path.dirname(script_path))

software_injectors_path = os.path.join(llfiroot, 'runtime_lib/_CustomSoftwareFaultInjectors.cpp')
software_failures_passes_dir = os.path.join(llfiroot, 'llvm_passes/software_failures/')
cmakelists = os.path.join(llfiroot, 'llvm_passes/CMakeLists.txt')

setup_script = os.path.join(llfiroot, 'setup.py')

#template path
config_dir = os.path.join(script_path, 'config')
custom_injectors_yaml = os.path.join(config_dir, 'custom_injectors.yaml')
injector_template = os.path.join(config_dir, 'NewInjectorTemplate.cpp')
single_template = os.path.join(config_dir, 'TargetSingleTemplate.cpp')
all_template = os.path.join(config_dir, 'TargetAllTemplate.cpp')
multisrc_template = os.path.join(config_dir, 'TargetMultiSourceTemplate.cpp')

################################################################################

#read .yaml file, and calculates the number of trigger points

def read_input_fidl():
  global F_Class, F_Mode, SpecInstsIndexes, numOfSpecInsts, Insts, custom_injector, action, reg_type, trigger_type, wildcard
  wildcard = False

  input_fidl = name

  # Check for Input FIDL's presence
  try:
    f = open(input_fidl, 'r')
  except:
    print('Error: Specified FIDL config file (%s) not found!' % input_fidl)
    exit(1)
  
  # Check for correct YAML formatting
  try:
    doc = yaml.load(f)
    f.close()
  except:
    print('Error: %s is not formatted in proper YAML format (reminder: use spaces, not tabs)' % input_fidl)
    exit(1)

  # Load values and check if FIDL options are valid
  
  try:
    F_Class = doc['Failure_Class']
    F_Mode = doc['Failure_Mode']
    nfm = doc['New_Failure_Mode']
    
    # parses 'Trigger'
    trigger = nfm['Trigger']
    
    if 'call' in trigger:
      Insts = trigger['call']
      trigger_type = 'call'
      
      # parses 'Target'
      target = nfm['Target']
      if 'src' in target and 'dst' in target:
        raise Exception('Error: Invalid trigger module (both src and dst usage not allowed)')
      elif 'src' in target:
        insts = target['src']
        if (set(insts) != set(Insts) or # need to specify at least one src for each instruction
            bool([inst for inst in insts.values() if inst == None or inst == [] or inst == '' or not isinstance(inst, list)])): # check that the specified src's aren't empty, an empty list, or an empty string, or isn't a list
          raise Exception("Error: Invalid number/name of src's in Target, or Target sources are not specified as list!")

        if 'all' in insts and len(insts) != 1: 
          raise Exception('Error: When instrumenting all call instruction, only 1 register can be specified!')
          
        if '*' in Insts[0]:
          Insts = {}
          for key in insts:
            new_key = key.replace('*', '')
            Insts[new_key] = insts[key]
          wildcard = True
        else:  
          Insts = insts
        reg_type = 'src'
      elif 'dst' in target:
        reg_type = 'dst'
      # elif 'RetVal' in target:
      #  reg_type = 'RetVal'
      else:
        raise Exception('Error: Invalid register target type!')
    elif 'return' in trigger:
      #Insts = trigger['RetVal']
      trigger_type = 'return'
    else:
      raise Exception('Error: Trigger option (call, or ret) not found!')
      
    # parses 'Trigger*'
    if 'Trigger*' in nfm:
      trigger_s = nfm['Trigger*']
      SpecInstsIndexes = ', '.join(str(s) for s in trigger_s)
      numOfSpecInsts = len(trigger_s)
    else:
      SpecInstsIndexes = ''
      numOfSpecInsts = 0
      
    # parses 'Action'
    action = nfm['Action']
    if 'Perturb' in action:
      perturb = action['Perturb']
      if 'Custom_Injector' in perturb:
        custom_injector = doc['Custom_Injector']
      
  except Exception as e:
    raise e

################################################################################

def gen_ftrigger_single():
  # convert trigger and target of .fidl file into appropriate llvm passes
  lines = read_file(single_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (F_Class, F_Mode))
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1, '    _%s_%sInstSelector() {' % (F_Class, F_Mode))
  
  i = lines.index('//fidl_3')
  for n in Insts:
    lines.insert(i + 1, '            funcNames.insert(std::string("%s"));' % n) 
    
  i = lines.index('//fidl_4')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (F_Class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (F_Mode))
  	
  lines.insert(lines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))

  i = lines.index('//fidl_6')
  if not wildcard:
    lines.insert(i + 1, '        return funcNames.find(func_name) != funcNames.end() && isTargetLLFIIndex(inst);')
  else:
    lines.insert(i + 1, '        return key_partially_matches(func_name) != funcNames.end() && isTargetLLFIIndex(inst);')
    
  i = lines.index('//fidl_7')
  lines.insert(i + 1, '        const long numOfSpecInsts = %s;' % (numOfSpecInsts))
  lines.insert(i + 2, '        const long IndexOfSpecInsts[] = {%s};' % (SpecInstsIndexes))
  
  lines.append('std::set<std::string> _%s_%sInstSelector::funcNames;\n' % (F_Class, F_Mode))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (F_Mode, F_Class, F_Class, F_Mode))
  # change reg_type
  if reg_type == 'src':
  	lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncArgRegSelector(%s));\n\n}\n' % (F_Mode, F_Class, next(iter(Insts.values()))[0]))
  elif reg_type == 'dst':
  	lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncDestRegSelector());\n\n}\n' % (F_Mode, F_Class))
  
  return lines
  
################################################################################
def gen_ftrigger_all():

  lines = read_file(all_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (F_Class, F_Mode))
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (F_Class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (F_Mode))
  lines.insert(i + 3, '        info["injector"] = "%s";' % (injector))
  if trigger_type == 'return':
    lines.insert(i + 4, '        info["targets"] = "return";')
  else:
    lines.insert(i + 4, '        info["targets"] = "all-call-instructions";')
  
  i = lines.index('//fidl_3')
  if trigger_type == 'return':
    lines.insert(i + 1, '        return isa<ReturnInst>(inst) && isTargetLLFIIndex(inst);')
  else:
    lines.insert(i + 1, '        return isa<CallInst>(inst) && isTargetLLFIIndex(inst);')
  
  i = lines.index('//fidl_4')
  lines.insert(i + 1, '        const long numOfSpecInsts = %s;' % (numOfSpecInsts))
  lines.insert(i + 2, '        const long IndexOfSpecInsts[] = {%s};' % (SpecInstsIndexes))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (F_Mode, F_Class, F_Class, F_Mode))
  if trigger_type == 'return':
    lines.append('static RegisterFIRegSelector B("%s(%s)", new RetValRegSelector());\n\n}\n' % (F_Mode, F_Class))
  else:
    if reg_type == 'src':
  	  lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncArgRegSelector(%s));\n\n}\n' % (F_Mode, F_Class, next(iter(Insts.values()))[0]))
    elif reg_type == 'dst':
  	  lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncDestRegSelector());\n\n}\n' % (F_Mode, F_Class))
  
  return lines
  
################################################################################
  
def gen_ftrigger_multisrc():
  lines = read_file(multisrc_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (F_Class, F_Mode)) # Trigger: "fread"
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1,'    _%s_%sInstSelector () {' % (F_Class,F_Mode))
  
  i = lines.index('//fidl_3')
  for inst in Insts:
    lines.insert(i + 1, '            funcNamesTargetArgs["%s"] = std::set<int>();' % inst)
    for reg in Insts[inst]:
      lines.insert(i + 2, '            funcNamesTargetArgs["%s"].insert(%s);' % (inst, reg))
     
  i = lines.index('//fidl_4')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (F_Class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (F_Mode))
  
  lines.insert(lines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))
  
  i = lines.index('//fidl_6')
  if not wildcard:
    lines.insert(i + 1, '        if (funcNamesTargetArgs.find(func_name) == funcNamesTargetArgs.end()) {')
    lines.insert(i + 2, '            return false;')
    lines.insert(i + 3, '        }')
    lines.insert(i + 4, '        for (std::set<int>::iterator SI = funcNamesTargetArgs[func_name].begin(); SI != funcNamesTargetArgs[func_name].end(); SI++) {')
  else:
    lines.insert(i + 1, '        std::map<std::string, std::set<int> >::iterator it = key_partially_matches(func_name);')
    lines.insert(i + 2, '        if (it == funcNamesTargetArgs.end()) {')
    lines.insert(i + 3, '            return false;')
    lines.insert(i + 4, '        }')
    lines.insert(i + 5, '        for (std::set<int>::iterator SI = it->second.begin(); SI != it->second.end(); SI++) {')
  
  i = lines.index('//fidl_7')
  if not wildcard:
    lines.insert(i + 1, '        return funcNamesTargetArgs.find(func_name) != funcNamesTargetArgs.end() && isTargetLLFIIndex(inst);')
  else:
    lines.insert(i + 1, '        return key_partially_matches(func_name) != funcNamesTargetArgs.end() && isTargetLLFIIndex(inst);')
  
  i = lines.index('//fidl_8')
  lines.insert(i + 1, '        const long numOfSpecInsts = %s;' % (numOfSpecInsts))
  lines.insert(i + 2, '        const long IndexOfSpecInsts[] = {%s};' % (SpecInstsIndexes))

  i = lines.index('//fidl_9')
  lines.insert(i + 1, 'std::map<std::string, std::set<int> >  _%s_%sInstSelector::funcNamesTargetArgs;\n' % (F_Class, F_Mode))
  lines.insert(i + 2, 'class _%s_%sRegSelector: public SoftwareFIRegSelector {' % (F_Class, F_Mode))  
  
  lines.insert(lines.index('//fidl_10') + 1, '        if (_%s_%sInstSelector::isTarget(CI, reg)) {\n            return true;' % (F_Class, F_Mode))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (F_Mode, F_Class, F_Class, F_Mode))
  lines.append('static RegisterFIRegSelector B("%s(%s)", new _%s_%sRegSelector());\n\n}\n'%(F_Mode, F_Class, F_Class, F_Mode))
  
  return lines
  
################################################################################
  
def FTriggerGenerator() :
  # complete instrumenting pass development by printing the pass content into a file.
  # write to a file
  filename = '_%s_%sSelector.cpp' % (F_Class, F_Mode)
  filepath = os.path.join(software_failures_passes_dir, filename)
    
  if trigger_type == 'return' or 'all' in Insts: # targering all 'call' or all 'ret'
    write_file(filepath, gen_ftrigger_all())
    print('Instrument module created.')
  elif reg_type == 'src' and not is_one_src_register(): # multisrc
    write_file(filepath, gen_ftrigger_multisrc())
    print('Instrument module created.')
  elif reg_type == 'src' or reg_type == 'dst': # dst or singlesrc
    write_file(filepath, gen_ftrigger_single())
    print('Instrument module created.')
  else:
    print('Check your target format!')
    exit(1)
  
  # modify llvm_pass/CMakeLists.txt
  l = read_file(cmakelists)
  try:
    l.index('  software_failures/%s' % filename) 
  except:
    l.insert(l.index("  #FIDL - DO NOT MODIFY UNTIL '#END'") + 1, '  software_failures/%s' % filename)
    write_file(cmakelists, l)
   
################################################################################
   
# checks if we are only instrumenting a single src register

def is_one_src_register():
  init_val = next(iter(Insts.values()))[0]
  for inst in Insts.values():
    if len(inst) > 1 or inst[0] != init_val:
      return False
  
  return True
      
################################################################################

def FInjectorGenerator():
  global injector

  name = '%s(%s)' % (F_Mode, F_Class)
  selectorfilename = '_%s_%sSelector.cpp' % (F_Class, F_Mode)
  code = []
  injector = ''
  
  insert = '_%s_%sFIDLInjector("%s(%s)",' % (F_Class, F_Mode, F_Mode, F_Class)
  
  if 'Corrupt' in action:
    code.append('static RegisterFaultInjector %s BitCorruptionInjector::getBitCorruptionInjector());' % (insert))
    injector = 'BitCorruptionInjector';
  elif 'Freeze' in action:	
    code.append('static RegisterFaultInjector %s new HangInjector());' % (insert))
    injector = 'HangInjector'
  elif 'Delay' in action:	 
    code.append('static RegisterFaultInjector %s new SleepInjector());' % (insert))
    injector = 'SleepInjector'
  elif 'Perturb' in action:
    perturb = action['Perturb']
    
    # certain perturb actions needs more information
    option = 'false'
    value = '-40'
    if 'option' in action:
      if action['option']:
        option = 'true'
      else:
        option = 'false'
    if 'value' in action:
      value = action['value']
    
    if 'MemoryLeakInjector' in perturb:
      code.append('static RegisterFaultInjector %s new MemoryLeakInjector());' % (insert))
      injector = 'MemoryLeakInjector'
    elif 'ChangeValueInjector' in perturb:
      code.append('static RegisterFaultInjector %s new ChangeValueInjector(%s, %s));' % (insert, value, option))
      injector = 'MemoryLeakInjector'
    elif 'InappropriateCloseInjector' in perturb:
      code.append('static RegisterFaultInjector %s new InappropriateCloseInjector(%s));' % (insert, option))
      injector = 'MemoryLeakInjector'
    elif 'MemoryExhaustionInjector' in perturb:
      code.append('static RegisterFaultInjector %s new MemoryExhaustionInjector(%s));' % (insert, option))
      injector = 'MemoryLeakInjector'
    elif 'WrongFormatInjector' in perturb:
      code.append('static RegisterFaultInjector %s new WrongFormatInjector());' % (insert))
      injector = 'MemoryLeakInjector'
    elif 'PthreadDeadLockInjector' in perturb:
      code.append('static RegisterFaultInjector %s new PthreadDeadLockInjector());' % (insert))
      injector = 'MemoryLeakInjector'
    elif 'PthreadThreadKillerInjector' in perturb:
      code.append('static RegisterFaultInjector %s new PthreadThreadKillerInjector());' % (insert))
      injector = 'MemoryLeakInjector'
    elif 'PthreadRaceConditionInjector' in perturb:
      code.append('static RegisterFaultInjector %s new PthreadRaceConditionInjector());' % (insert))
      injector = 'PthreadRaceConditionInjector'
    elif 'Custom_Injector' in perturb:
      code.extend(gen_custom_injector(insert))
      injector = 'CustomInjector'
    else:
      print('Error: Invalid Perturb Injector!')
      exit(1)
  else:
    print("Error: Invalid 'Action:' field in yaml file!")
    exit(1)
    
  return {'name': name, 'selectorfilename': selectorfilename, 'code': '\n'.join(code)}
  
################################################################################

def generate_FI_file():
  content = []
  content.append('// DO NOT MODIFY\n#include "_SoftwareFaultInjectors.cpp"\n')
  for i in custom_injectors:
    content.append('// ' + i['name'])
    content.append(i['code'] + '\n')
    
  write_file(os.path.join(llfiroot, 'runtime_lib/_FIDLSoftwareFaultInjectors.cpp'), content)
  
################################################################################

def gen_custom_injector(insert):
  global custom_injector
  
  # format the custom injector lines
  custom_injector = '        ' + custom_injector                # add spaces before the first line
  custom_injector = custom_injector.rstrip('\n')                # remove last \n character
  custom_injector = custom_injector.replace('\n', '\n        ') # add spaces after every \n character
  
  # read template
  NInjectorLines = read_file(injector_template)
  
  # modify template
  NInjectorLines[0] = 'class _%s_%sFInjector : public SoftwareFaultInjector {' % (F_Class, F_Mode)
  NInjectorLines[5] = custom_injector
  NInjectorLines.append('static RegisterFaultInjector %s new _%s_%sFInjector());' % (insert, F_Class, F_Mode)) 
  
  return NInjectorLines

################################################################################

def read_file(file_name):
  with open(file_name) as f:
    lines = f.read().splitlines()
  return lines
  
def write_file(file_name, lines):
  with open(file_name, 'w') as f:
    for line in lines:
      f.write('%s\n' % line)
      
################################################################################

def parse_args(args):
  global option, name
  option = '-a'
  for a in args:
    if a == '-r':
      option = '-r'
    elif a == '-l':
      option = '-l'
    else:
      name = a
      
################################################################################

def read_custom_injectors():
  global custom_injectors, doc
  f = open(custom_injectors_yaml)
  doc = yaml.load(f)
  custom_injectors = doc['custom_injectors']
  f.close()

################################################################################

def main(args):
  global custom_injectors

  parse_args(args)
  read_custom_injectors()
  
  if option == '-r':
    if name.isdigit():
      i = int(name)
      try:
        print('Deleting ' + custom_injectors[i]['name'])
        selectorfilename = [custom_injectors[i]['selectorfilename']]
        del custom_injectors[i]
      except IndexError:
        print('Error: %s is not a valid index!' % name)
        exit(1)
    elif name == 'all':
      print('Deleting all custom injectors!')
      selectorfilename = []
      for i in custom_injectors:
        selectorfilename.append(i['selectorfilename'])
      custom_injectors = doc['custom_injectors'] = []
    else:
      selectorfilename = []
      print('Deleting ' + name)
      for i in custom_injectors:
        if i['name']  == name:
          selectorfilename = [i['selectorfilename']]
          custom_injectors.remove(i)
          break
          
      if selectorfilename == []:
        print('Error: %s is not a custom injector!' % name)
        exit(1)
      
    # write the custom injectors yaml
    f = open(custom_injectors_yaml, 'w')
    yaml.dump(doc, f)
    f.close()
    
    # modify llvm_pass/CMakeLists.txt and remove the selector file
    l = read_file(cmakelists)
    for n in selectorfilename:
      try:
        l.remove('  software_failures/%s' % n) 
      except Exception:
        pass
      
      try:
        os.remove(os.path.join(software_failures_passes_dir, n))
      except Exception:
        pass
      
    write_file(cmakelists, l)

    # generate custom software fault injector file
    generate_FI_file()
      
  elif option == '-l':
    print('Current custom software fault injectors:')
    if custom_injectors == []:
      print('No injector exists!')
    else:
      for i, n in enumerate(custom_injectors):
        print("%i %s" % (i, n['name']))
      
  else: # add an injector module
    read_input_fidl()
    print('Generating %s(%s) injector!' % (F_Mode, F_Class))
    
    # generate and insert new software fault injector into the custom injector yaml
    new_injector = FInjectorGenerator()
    found = False
    for i, n in enumerate(custom_injectors):
      if n['name'] == new_injector['name']:
        custom_injectors[i] = new_injector
        found = True
        break
    if not found:
      custom_injectors.append(new_injector)
    
    # write the custom injectors yaml
    f = open(custom_injectors_yaml, 'w')
    yaml.dump(doc, f)
    f.close()
    
    # generate custom software fault injector file
    generate_FI_file()
    
    # generate trigger/selector file
    FTriggerGenerator()
    
    print ('Injector module created.')

################################################################################

if __name__ == '__main__':
  main(sys.argv[1:])

