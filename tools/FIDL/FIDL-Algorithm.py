#! /usr/bin/env python3

"""
(%prog)s takes a .fidl and generates ... 

Usage: %(prog)s [OPTIONS] <fidl .yaml>

List of options:
-r:    removes the specified fidl .yaml
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
custom_injectors_yaml = 'custom_injectors.yaml'
software_failures_passes_dir = os.path.join(llfiroot, 'llvm_passes/software_failures/')
cmakelists = os.path.join(llfiroot, 'llvm_passes/CMakeLists.txt')

setup_script = os.path.join(llfiroot, 'setup.py')

################################################################################

#read .yaml file, and calculates the number of trigger points

def read_input_fidl():
  global F_Class, F_Mode, SpecInstsIndexes, numOfSpecInsts, Insts, custom_injector, action, reg_type, trigger_type

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
        else:
          Insts = insts
        reg_type = 'src'
      elif 'dst' in target:
        reg_type = 'dst'
      elif 'RetVal' in target:
        reg_type = 'RetVal'
      else:
        raise Exception('Error: Invalid register target type!')
    elif 'RetVal' in trigger:
      Insts = trigger['RetVal']
      trigger_type = 'RetVal'
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
  # os.chdir("llfisrc/Templates/")
  MapLines = read_file('TargetDestinationTemplate.cpp')
  
  # print(MapLines)
  M1 = MapLines.index('//fidl_1')
  
  MapLines.insert(M1 + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (F_Class, F_Mode))
  M2 = MapLines.index('//fidl_2')
  MapLines.insert(M2 + 1, '    _%s_%sInstSelector() {' % (F_Class, F_Mode))
  M3 = MapLines.index('//fidl_3')
  for i in Insts:
    MapLines.insert(M3 + 1, '        funcNames.insert(std::string("%s"));' % i) 
  M4 = MapLines.index('//fidl_4')
  MapLines.insert(M4 + 1, '        info["failure_class"] = "%s";' % (F_Class))
  MapLines.insert(M4 + 2, '        info["failure_mode"] = "%s";' % (F_Mode))
  MapLines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (F_Mode, F_Class, F_Class, F_Mode))
  
  # change reg_type
  if reg_type == 'src':
  	MapLines.append('static RegisterFIRegSelector B("%s(%s)", new FuncArgRegSelector(%s));\n\n}\n' % (F_Mode, F_Class, next(iter(Insts.values()))[0]))
  elif reg_type == 'dst':
  	MapLines.append('static RegisterFIRegSelector B("%s(%s)", new FuncDestRegSelector());\n\n}\n' % (F_Mode, F_Class))
  # @PHIL Bugfix July 22 # doesnt work still
  elif reg_type == 'RetVal': 
  	PassLines.append('static RegisterFIRegSelector B("%s(%s)", new RetValRegSelector());\n\n}\n' % (F_Mode, F_Class))
  	
  MapLines.insert(MapLines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))

  AA = MapLines.index('//fidl_6')

  MapLines.insert(AA + 1, '                long numOfSpecInsts = %s;' % (numOfSpecInsts))
  MapLines.insert(AA + 2, '                long IndexOfSpecInsts[] = {%s};' % (SpecInstsIndexes))
  
  return MapLines
  
################################################################################
  
def gen_ftrigger_multisrc():
  PassLines = read_file('TargetSourceTemplate.cpp')
  
  A = PassLines.index('//fidl_1')
  PassLines.insert(A + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (F_Class,F_Mode)) # Trigger: "fread"
  B = PassLines.index('//fidl_2')
  PassLines.insert(B + 1,'    _%s_%sInstSelector () {' % (F_Class,F_Mode))
  X = PassLines.index('//fidl_3')
           
  for inst in Insts:
    PassLines.insert(X + 1, '            funcNamesTargetArgs["%s"] = std::set<int>();' % inst)
    for reg in Insts[inst]:
      PassLines.insert(X + 2, '            funcNamesTargetArgs["%s"].insert(%s);' % (inst, reg))
     
  C = PassLines.index('//fidl_4')
  PassLines.insert(C + 1, '        info["failure_class"] = "%s";' % (F_Class))
  PassLines.insert(C + 2, '        info["failure_mode"] = "%s";' % (F_Mode))

  F = PassLines.index('    virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {')
  PassLines.insert(F + 5, '        if (_%s_%sInstSelector::isTarget(CI, reg)) {\n            return true;\n        }' % (F_Class,F_Mode))
  PassLines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (F_Mode, F_Class, F_Class, F_Mode))
  
  PassLines.append('static RegisterFIRegSelector B("%s(%s)", new _%s_%sRegSelector());\n\n}\n'%(F_Mode, F_Class, F_Class, F_Mode))
  # print(PassLines)
  
  PassLines.insert(PassLines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))
    
  AA = PassLines.index('//fidl_6')

  PassLines.insert(AA + 1, '                long numOfSpecInsts = %s;' % (numOfSpecInsts))
  PassLines.insert(AA + 2, '                long IndexOfSpecInsts[] = {%s};' % (SpecInstsIndexes))

  F = PassLines.index('//fidl_7')
  PassLines.insert(F + 1, 'std::map<std::string, std::set<int> >  _%s_%sInstSelector::funcNamesTargetArgs;\n' % (F_Class, F_Mode))
  PassLines.insert(F + 2, 'class _%s_%sRegSelector: public SoftwareFIRegSelector {' % (F_Class, F_Mode))  
  
  # @PHIL Bugfix July 21
  PassLines.insert(PassLines.index('//fidl_8') + 1, '        if (_%s_%sInstSelector::isTarget(CI, reg)) {\n            return true;' % (F_Class, F_Mode))
  
  return PassLines
  
################################################################################
  
def FTriggerGenerator() :
  # complete instrumenting pass development by printing the pass content into a file.
  # write to a file
  filename = '_%s_%sSelector.cpp' % (F_Class, F_Mode)
  filepath = os.path.join(software_failures_passes_dir, filename)
    
  if reg_type == 'src' and not is_one_src_register(): # multisrc
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

  """
  InjectorLines = read_file('Built-in-FITemplate.cpp')
  
  M = InjectorLines.index('static RegisterFaultInjector AN("DataCorruption(Data)", BitCorruptionInjector::getBitCorruptionInjector());')
  N = InjectorLines.index('static RegisterFaultInjector CD("NoAck(MPI)", new HangInjector());')
  O = InjectorLines.index('static RegisterFaultInjector DB("CPUHog(Res)", new SleepInjector());')
  P = InjectorLines.index('static RegisterFaultInjector BA("MemoryLeak(Res)", new MemoryLeakInjector());')
  S = InjectorLines.index('static RegisterFaultInjector EH("PacketStorm(MPI)", new ChangeValueInjector(-40, false));')
  T = InjectorLines.index('static RegisterFaultInjector FB("NoClose(API)", new InappropriateCloseInjector(false));')
  U = InjectorLines.index('static RegisterFaultInjector HB("LowMemory(Res)", new MemoryExhaustionInjector(false));')
  V = InjectorLines.index('static RegisterFaultInjector IB("WrongSavedFormat(I/O)", new WrongFormatInjector());')
  W = InjectorLines.index('static RegisterFaultInjector JA("DeadLock(Res)", new PthreadDeadLockInjector());')
  X = InjectorLines.index('static RegisterFaultInjector KA("ThreadKiller(Res)", new PthreadThreadKillerInjector());')
  Y = InjectorLines.index('static RegisterFaultInjector LA("RaceCondition(Timing)", new PthreadRaceConditionInjector());')
  """
  name = '%s(%s)' % (F_Mode, F_Class)
  selectorfilename = '_%s_%sSelector.cpp' % (F_Class, F_Mode)
  code = []
  injector = ''

  # print(Type)     
  if 'Corrupt' in action:
    code.append('static RegisterFaultInjector AO("%s(%s)", BitCorruptionInjector::getBitCorruptionInjector());' % (F_Mode, F_Class))
    injector = 'BitCorruptionInjector';
    # print('i am in corrupt')
    # print("compilation successful")
  elif 'Freeze' in action:	
    code.append('static RegisterFaultInjector CE("%s(%s)", new HangInjector());' % (F_Mode, F_Class))
    injector = 'HangInjector'
    # print('i am in freeze')
    # print("compilation successful")
  elif 'Delay' in action:	 
    code.append('static RegisterFaultInjector DC("%s(%s)", new SleepInjector());' % (F_Mode, F_Class))
    injector = 'SleepInjector'
    # print('i am in delay')
    # print("compilation successful")
  elif 'Perturb' in action:
    perturb = action['Perturb']
    if 'MemoryLeakInjector' in perturb:
      code.append('static RegisterFaultInjector BB("%s(%s)", new MemoryLeakInjector());' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print('i am in built-in perturb') 
      # print("compilation successful")
    elif 'ChangeValueInjector' in perturb:
      code.append('static RegisterFaultInjector EI("%s(%s)", new ChangeValueInjector(-40, false));' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'InappropriateCloseInjector' in perturb:
      code.append('static RegisterFaultInjector FC("%s(%s)", new InappropriateCloseInjector(false));' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'MemoryExhaustionInjector' in perturb:
      code.append('static RegisterFaultInjector HC("%s(%s)", new MemoryExhaustionInjector(false));' %( F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'WrongFormatInjector' in perturb:
      code.append('static RegisterFaultInjector IC("%s(%s)", new WrongFormatInjector());' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'PthreadDeadLockInjector' in perturb:
      code.append('static RegisterFaultInjector JB("%s(%s)", new PthreadDeadLockInjector());' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'PthreadThreadKillerInjector' in perturb:
      code.append('static RegisterFaultInjector KB("%s(%s)", new PthreadThreadKillerInjector());' % (F_Mode, F_Class))
      injector = 'MemoryLeakInjector'
      # print("compilation successful")
    elif 'PthreadRaceConditionInjector' in perturb:
      code.append('static RegisterFaultInjector LB("%s(%s)", new PthreadRaceConditionInjector());' % (F_Mode, F_Class))
      injector = 'PthreadRaceConditionInjector'
      # print("compilation successful")
    elif 'Custom_Injector' in perturb:
      code.extend(gen_custom_injector())
      injector = 'CustomInjector'
    else:
      print('Error: Invalid Perturb Injector!')
      exit(1)
  else:
    print('Error: Invalid Action!')
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

def gen_custom_injector():
  global custom_injector
  
  # format the custom injector lines
  custom_injector = '        ' + custom_injector                # add spaces before the first line
  custom_injector = custom_injector.rstrip('\n')                # remove last \n character
  custom_injector = custom_injector.replace('\n', '\n        ') # add spaces after every \n character
  
  # read template
  NInjectorLines = read_file('NewInjectorTemplate.cpp')
  
  # modify template
  NInjectorLines[0] = 'class %s_%sFInjector : public SoftwareFaultInjector {' % (F_Class, F_Mode)
  NInjectorLines[5] = custom_injector
  NInjectorLines.append('static RegisterFaultInjector X("%s(%s)", new %s_%sFInjector());' % (F_Mode, F_Class, F_Class, F_Mode)) 
  
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

  parse_args(args)
  read_custom_injectors()
  
  if option == '-r':
    selectorfilename = ''
    print('Deleting ' + name)
    for i in custom_injectors:
      if i['name']  == name:
        selectorfilename = i['selectorfilename']
        custom_injectors.remove(i)
        break
        
    if selectorfilename == '':
      print("Error: %s is not a custom injector!" % name)
      exit(1)
      
    # write the custom injectors yaml
    f = open(custom_injectors_yaml, 'w')
    yaml.dump(doc, f)
    f.close()
    
    # modify llvm_pass/CMakeLists.txt
    l = read_file(cmakelists)
    try:
      l.remove('  software_failures/%s' % selectorfilename) 
      write_file(cmakelists, l)
    except Exception:
      pass
    
    # remove the selector file
    os.remove(os.path.join(software_failures_passes_dir, selectorfilename))
    
    # generate custom software fault injector file
    generate_FI_file()
      
  elif option == '-l':
    print('Current custom software fault injectors:')
    for i in custom_injectors:
      print(i['name'])
      
  else: 
    read_input_fidl()
    
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

