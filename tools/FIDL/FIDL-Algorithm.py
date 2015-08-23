#! /usr/bin/env python3

"""
%(prog)s takes a .fidl and generates ... 

Usage: %(prog)s [OPTIONS] <fidl .yaml>

List of options:
-r:    removes the specified injector by '<FMode>(<FClass>)'
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

script_dir = os.path.realpath(os.path.dirname(__file__))
prog = os.path.basename(sys.argv[0])

llfiroot = os.path.dirname(os.path.dirname(script_dir))

fidl_runtime_path = os.path.join(llfiroot, 'runtime_lib/_FIDLSoftwareFaultInjectors.cpp')
software_failures_passes_dir = os.path.join(llfiroot, 'llvm_passes/software_failures/')
cmakelists = os.path.join(llfiroot, 'llvm_passes/CMakeLists.txt')

setup_script = os.path.join(llfiroot, 'setup.py')

config_dir = os.path.join(script_dir, 'config')

all_injectors_yaml = os.path.join(config_dir, 'injectors.yaml')
default_failures_yaml = os.path.join(config_dir, 'default_failures.yaml')

injector_template = os.path.join(config_dir, 'NewInjectorTemplate.cpp')
single_template = os.path.join(config_dir, 'TargetSingleTemplate.cpp')
all_template = os.path.join(config_dir, 'TargetAllTemplate.cpp')
multisrc_template = os.path.join(config_dir, 'TargetMultiSourceTemplate.cpp')

################################################################################

def read_file(file_name):
  with open(file_name) as f:
    lines = f.read().splitlines()
  return lines
  
def write_file(file_name, lines):
  with open(file_name, 'w') as f:
    for line in lines:
      f.write('%s\n' % line)

def write_yaml(obj, path):
  f = open(path, 'w')
  yaml.dump(obj, f)
  f.close()

def read_input_yaml(filename):
  # Check for Input FIDL's presence
  try:
    f = open(filename, 'r')
  except:
    print('Error: Specified FIDL config file (%s) not found!' % (filename), file = sys.stderr)
    exit(1)
  
  # Check for correct YAML formatting
  try:
    doc = yaml.load(f)
    f.close()
  except:
    print('Error: %s is not formatted in proper YAML format (reminder: use spaces, not tabs)' % (filename), file = sys.stderr)
    exit(1)
    
  return doc

def parse_input(doc):
  options = {}
  # Load values and check if FIDL options are valid
  try:
    options['f_class'] = doc['Failure_Class']
    options['f_mode'] = doc['Failure_Mode']
    nfm = doc['New_Failure_Mode']
    
    # parses 'Trigger'
    trigger = nfm['Trigger']
    
    if 'call' in trigger or 'call*' in trigger:
      if 'call' in trigger:
        options['insts'] = trigger_insts = trigger['call']
        options['trigger_type'] = 'call' 
      else:
        options['insts'] = trigger_insts = trigger['call*']
        options['trigger_type'] = 'call*'
        if 'all' in trigger_insts:
          raise Exception("Error: Cannot instrument both 'call*' and 'all'!")
      
      # parses 'Target'
      target = nfm['Target']
      if 'src' in target and 'dst' in target:
        raise Exception('Error: Invalid trigger module (both src and dst usage not allowed)')
      elif 'src' in target:
        target_insts = target['src']
        if (set(target_insts) != set(trigger_insts) or # need to specify at least one src for each instruction
            bool([target_inst for inst in target_insts.values() if inst == None or inst == [] or inst == '' or not isinstance(inst, list)])): # check that the specified src's aren't empty, an empty list, or an empty string, or isn't a list
          raise Exception("Error: Invalid number/name of src's in Target, or Target sources are not specified as list!")

        if 'all' in target_insts and len(target_insts) != 1: 
          raise Exception('Error: When instrumenting all call instruction, only 1 register can be specified!')
           
        options['insts'] = target_insts # replace with target insts if we're dealing with src
        options['reg_type'] = 'src'
      elif 'dst' in target:
        options['reg_type'] = 'dst'
      else:
        raise Exception('Error: Invalid register target type!')
    elif 'return' in trigger:
      options['trigger_type'] = 'return'
      options['reg_type'] = 'ret' # unused
      options['insts'] = [] # unused
    else:
      raise Exception('Error: Trigger option (call, call*, or ret) not found!')
      
    # parses 'Trigger*'
    if 'Trigger*' in nfm:
      options['trigger_s'] = nfm['Trigger*']
      
    # parses 'Action'
    options['action'] = action = nfm['Action']
    if 'Perturb' in action:
      perturb = action['Perturb']
      if 'Custom_Injector' in perturb:
        options['custom_injector'] = doc['Custom_Injector']
      
  # raises any errors occured during parsing
  except Exception as e:
    raise e
    
  # {f_class, f_mode, trigger_type, reg_type, action, injector* (from gen_runtime_code())}
  # {insts* (if src selected), trigger_s* (if indices selected), custom_injector* (if implemented)}
  return options

################################################################################

def gen_ftrigger_single(options):
  f_class = options['f_class']
  f_mode = options['f_mode']
  trigger_type = options['trigger_type']
  injector = options['injector']
  insts = options['insts']
  reg_type = options['reg_type']

  # convert trigger and target of .fidl file into appropriate llvm passes
  lines = read_file(single_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (f_class, f_mode))
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1, '    _%s_%sInstSelector() {' % (f_class, f_mode))
  
  i = lines.index('//fidl_3')
  for n in insts:
    lines.insert(i + 1, '            funcNames.insert(std::string("%s"));' % n) 
    
  i = lines.index('//fidl_4')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (f_class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (f_mode))
  	
  lines.insert(lines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))

  i = lines.index('//fidl_6')
  insert = ''
  if 'trigger_s' in options:
    insert = ' && isTargetLLFIIndex(inst)'
  if trigger_type != 'call*':
    lines.insert(i + 1, '        return funcNames.find(func_name) != funcNames.end()%s;' % (insert))
  else:
    lines.insert(i + 1, '        return key_partially_matches(func_name) != funcNames.end()%s;' % (insert))
    
  lines.insert(lines.index('//fidl_7') + 1, gen_targeted_indices(options))
  
  lines.append('std::set<std::string> _%s_%sInstSelector::funcNames;\n' % (f_class, f_mode))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (f_mode, f_class, f_class, f_mode))
  # change reg_type
  if reg_type == 'src':
  	lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncArgRegSelector(%s));\n\n}\n' % (f_mode, f_class, next(iter(insts.values()))[0]))
  elif reg_type == 'dst':
  	lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncDestRegSelector());\n\n}\n' % (f_mode, f_class))
  
  return lines

def gen_ftrigger_all(options):
  f_class = options['f_class']
  f_mode = options['f_mode']
  trigger_type = options['trigger_type']
  injector = options['injector']
  insts = options['insts']
  reg_type = options['reg_type']

  lines = read_file(all_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (f_class, f_mode))
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (f_class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (f_mode))
  lines.insert(i + 3, '        info["injector"] = "%s";' % (injector))
  if trigger_type == 'return':
    lines.insert(i + 4, '        info["targets"] = "return";')
  else:
    lines.insert(i + 4, '        info["targets"] = "all-call-instructions";')
  
  i = lines.index('//fidl_3')
  insert = ''
  if 'trigger_s' in options:
    insert = ' && isTargetLLFIIndex(inst)'
  if trigger_type == 'return':
    lines.insert(i + 1, '        return isa<ReturnInst>(inst)%s;' % (insert))
  else:
    lines.insert(i + 1, '        return isa<CallInst>(inst)%s;' % (insert))
  
  lines.insert(lines.index('//fidl_4') + 1, gen_targeted_indices(options))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (f_mode, f_class, f_class, f_mode))
  if trigger_type == 'return':
    lines.append('static RegisterFIRegSelector B("%s(%s)", new RetValRegSelector());\n\n}\n' % (f_mode, f_class))
  else:
    if reg_type == 'src':
  	  lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncArgRegSelector(%s));\n\n}\n' % (f_mode, f_class, next(iter(insts.values()))[0]))
    elif reg_type == 'dst':
  	  lines.append('static RegisterFIRegSelector B("%s(%s)", new FuncDestRegSelector());\n\n}\n' % (f_mode, f_class))
  
  return lines
  
def gen_ftrigger_multisrc(options):
  f_class = options['f_class']
  f_mode = options['f_mode']
  trigger_type = options['trigger_type']
  insts = options['insts']
  injector = options['injector']
  
  lines = read_file(multisrc_template)
  
  i = lines.index('//fidl_1')
  lines.insert(i + 1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector {' % (f_class, f_mode)) # Trigger: "fread"
  
  i = lines.index('//fidl_2')
  lines.insert(i + 1,'    _%s_%sInstSelector () {' % (f_class,f_mode))
  
  i = lines.index('//fidl_3')
  for inst in insts:
    lines.insert(i + 1, '            funcNamesTargetArgs["%s"] = std::set<int>();' % inst)
    for reg in insts[inst]:
      lines.insert(i + 2, '            funcNamesTargetArgs["%s"].insert(%s);' % (inst, reg))
     
  i = lines.index('//fidl_4')
  lines.insert(i + 1, '        info["failure_class"] = "%s";' % (f_class))
  lines.insert(i + 2, '        info["failure_mode"] = "%s";' % (f_mode))
  
  lines.insert(lines.index('//fidl_5') + 1, '        info["injector"] = "%s";' % (injector))
  
  i = lines.index('//fidl_6')
  if trigger_type != 'call*':
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
  insert = ''
  if 'trigger_s' in options:
    insert = ' && isTargetLLFIIndex(inst)'
  if trigger_type != 'call*':
    lines.insert(i + 1, '        return funcNamesTargetArgs.find(func_name) != funcNamesTargetArgs.end()%s;' % (insert))
  else:
    lines.insert(i + 1, '        return key_partially_matches(func_name) != funcNamesTargetArgs.end()%s;' % (insert))
  
  lines.insert(lines.index('//fidl_8') + 1, gen_targeted_indices(options))

  i = lines.index('//fidl_9')
  lines.insert(i + 1, 'std::map<std::string, std::set<int> >  _%s_%sInstSelector::funcNamesTargetArgs;\n' % (f_class, f_mode))
  lines.insert(i + 2, 'class _%s_%sRegSelector: public SoftwareFIRegSelector {' % (f_class, f_mode))  
  
  lines.insert(lines.index('//fidl_10') + 1, '        if (_%s_%sInstSelector::isTarget(CI, reg)) {\n            return true;' % (f_class, f_mode))
  
  lines.append('static RegisterFIInstSelector A("%s(%s)", new _%s_%sInstSelector());' % (f_mode, f_class, f_class, f_mode))
  lines.append('static RegisterFIRegSelector B("%s(%s)", new _%s_%sRegSelector());\n\n}\n' % (f_mode, f_class, f_class, f_mode))
  
  return lines
  
def gen_and_write_selector(options) :
  f_class = options['f_class']
  f_mode = options['f_mode']
  
  trigger_type = options['trigger_type']
  reg_type = options['reg_type']
  insts = options['insts']
  
  # complete instrumenting pass development by printing the pass content into a file.
  # write to a file
  filename = '_%s_%sSelector.cpp' % (f_class, f_mode)
  filepath = os.path.join(software_failures_passes_dir, filename)
    
  if trigger_type == 'return' or 'all' in insts: # targering all call instructions or all 'ret'
    write_file(filepath, gen_ftrigger_all(options))
  elif reg_type == 'src' and not is_one_src_register(insts): # multisrc
    write_file(filepath, gen_ftrigger_multisrc(options))
  elif reg_type == 'src' or reg_type == 'dst': # dst or singlesrc
    write_file(filepath, gen_ftrigger_single(options))
  else:
    print('Error: Invalid FIDL config!', file = sys.stderr)
    exit(1)
  
  # modify llvm_pass/CMakeLists.txt
  l = read_file(cmakelists)
  try:
    l.index('  software_failures/%s' % filename) 
  except:
    l.insert(l.index("  #FIDL - DO NOT MODIFY UNTIL '#END'") + 1, '  software_failures/%s' % filename)
    write_file(cmakelists, l)
    
  print('Selector/Instrument module created.')
   
# checks if we are only instrumenting a single src register
def is_one_src_register(insts):
  init_val = next(iter(insts.values()))[0]
  for inst in insts.values():
    if len(inst) > 1 or inst[0] != init_val:
      return False
  
  return True
  
def gen_targeted_indices(options):
  if 'trigger_s' in options:
    trigger_s = options['trigger_s']
    targeted_indices = ', '.join(str(s) for s in trigger_s)
    n = len(trigger_s)
  else:
    targeted_indices = ''
    n = 0
    
  return '        const long n = %s;\n' % (n) + \
         '        const long targeted_indices[] = {%s};' % (targeted_indices)
      
################################################################################

def gen_runtime_code(options, injectors_dict):
  f_class = options['f_class']
  f_mode = options['f_mode']
  action = options['action']
  
  name = '%s(%s)' % (f_mode, f_class)
  selectorfilename = '_%s_%sSelector.cpp' % (f_class, f_mode)
  code = []
  injector = '' # for use in info['injector'] in the selector file
  
  insert = '_%s_%sFIDLInjector("%s(%s)",' % (f_class, f_mode, f_mode, f_class)
  
  if 'Corrupt' in action:
    injector = 'BitCorruptionInjector';
    code.append('static RegisterFaultInjector %s BitCorruptionInjector::getBitCorruptionInjector());' % (insert))
  elif 'Freeze' in action:
    injector = 'HangInjector'
    code.append('static RegisterFaultInjector %s new HangInjector());' % (insert))
  elif 'Delay' in action:
    injector = 'SleepInjector'
    code.append('static RegisterFaultInjector %s new SleepInjector());' % (insert))
  elif 'Perturb' in action:
    perturb = action['Perturb']
    
    # certain perturb actions needs more information
    if 'option' in action:
      if action['option']:
        boolean = 'true'
      else:
        boolean = 'false'
    if 'value' in action:
      value = action['value']
    
    if 'MemoryLeakInjector' in perturb:
      injector = 'MemoryLeakInjector'
      code.append('static RegisterFaultInjector %s new MemoryLeakInjector());' % (insert))
    elif 'ChangeValueInjector' in perturb:
      injector = 'ChangeValueInjector'
      try:
        code.append('static RegisterFaultInjector %s new ChangeValueInjector(%s, %s));' % (insert, value, boolean))
      except NameError:
        print("Error: 'Perturb: %s' injector requires a integer value under 'Action: value:', and a boolean option under 'Action: option:'!" % (injector), file = sys.stderr)
        exit(1)
    elif 'InappropriateCloseInjector' in perturb:
      injector = 'InappropriateCloseInjector'
      try:
        code.append('static RegisterFaultInjector %s new InappropriateCloseInjector(%s));' % (insert, boolean))
      except NameError:
        print("Error: 'Perturb: %s' injector requires a boolean option under 'Action: option:'!" % (injector), file = sys.stderr)
        exit(1)
    elif 'MemoryExhaustionInjector' in perturb:
      injector = 'MemoryExhaustionInjector'
      try:
        code.append('static RegisterFaultInjector %s new MemoryExhaustionInjector(%s));' % (insert, boolean))
      except NameError:
        print("Error: 'Perturb: %s' injector requires a boolean option under 'Action: option:'!" % (injector), file = sys.stderr)
        exit(1)
    elif 'WrongFormatInjector' in perturb:
      injector = 'WrongFormatInjector'
      code.append('static RegisterFaultInjector %s new WrongFormatInjector());' % (insert))
    elif 'PthreadDeadLockInjector' in perturb:
      injector = 'PthreadDeadLockInjector'
      code.append('static RegisterFaultInjector %s new PthreadDeadLockInjector());' % (insert))
    elif 'PthreadThreadKillerInjector' in perturb:
      injector = 'PthreadThreadKillerInjector'
      code.append('static RegisterFaultInjector %s new PthreadThreadKillerInjector());' % (insert))
    elif 'PthreadRaceConditionInjector' in perturb:
      injector = 'PthreadRaceConditionInjector'
      code.append('static RegisterFaultInjector %s new PthreadRaceConditionInjector());' % (insert))
    elif 'Custom_Injector' in perturb:
      injector = 'CustomInjector'
      if 'custom_injector' in options:
        code.extend(gen_custom_injector(insert, f_class, f_mode, options['custom_injector']))
      else:
        print("Error: Custom_Injector specified in 'Perturb:' but not specified in .yaml file!", file = sys.stderr)
        exit(1)
    else:
      print('Error: Invalid Perturb Injector!', file = sys.stderr)
      exit(1)
  else:
    print("Error: Invalid 'Action:' field in yaml file!", file = sys.stderr)
    exit(1)
    
  options['injector'] = injector
  injectors_dict[name] = {'selectorfilename': selectorfilename, 'code': '\n'.join(code)}

def gen_runtime_file(injectors):
  content = []
  content.append('// DO NOT MODIFY\n#include "_SoftwareFaultInjectors.cpp"\n')
  
  content.append('/*********************')
  content.append(' * DEFAULT INJECTORS *')
  content.append(' *********************/\n')
  
  for key, value in injectors['default'].items():
    content.append('// ' + key)
    content.append(value['code'] + '\n')
    
  content.append('/********************')
  content.append(' * CUSTOM INJECTORS *')
  content.append(' ********************/\n')
    
  for key, value in injectors['custom'].items():
    content.append('// ' + key)
    content.append(value['code'] + '\n')
    
  write_file(fidl_runtime_path, content)

def gen_custom_injector(insert, f_class, f_mode, custom_injector):
  # format the custom injector lines
  custom_injector = '        ' + custom_injector                # add spaces before the first line
  custom_injector = custom_injector.rstrip('\n')                # remove last \n character
  custom_injector = custom_injector.replace('\n', '\n        ') # add spaces after every \n character
  
  # read template
  lines = read_file(injector_template)
  
  # modify template
  lines[0] = 'class _%s_%sFInjector : public SoftwareFaultInjector {' % (f_class, f_mode)
  lines[5] = custom_injector
  lines.append('static RegisterFaultInjector %s new _%s_%sFInjector());' % (insert, f_class, f_mode)) 
  
  return lines

################################################################################
  
# modify llvm_pass/CMakeLists.txt and remove the selector file
def del_selectors(selectorfilenames):
  l = read_file(cmakelists)
  for n in selectorfilenames:
    try:
      l.remove('  software_failures/%s' % n) 
    except Exception:
      pass
    try:
      os.remove(os.path.join(software_failures_passes_dir, n))
    except Exception:
      pass
  write_file(cmakelists, l)

def list_injectors(injector_type):
  all_injectors = read_input_yaml(all_injectors_yaml)
  injectors = all_injectors[injector_type]
  
  if injectors == {}:
    print('No injector exists!')
  else:
    for key in injectors:
      print(key)

def add_injectors(filename, injector_type):
  inp = read_input_yaml(filename)
  
  #TODO remove after
  if 'tests' in inp:
    c = inp['tests']
    inp = []
    for n in c:
      inp.append(n['FIDL'])
  
  all_injectors = read_input_yaml(all_injectors_yaml)
  injectors = all_injectors[injector_type]

  if isinstance(inp, list):
    for n in inp:
      options = parse_input(n) # parses yaml
      print('Generating %s(%s) injector!' % (options['f_mode'], options['f_class']))
      gen_runtime_code(options, injectors) # generates runtime fault injector code and insert runtime into a dictionary
      gen_and_write_selector(options) # generates selector file
  else:
    options = parse_input(inp) # parses yaml
    print('Generating %s(%s) injector!' % (options['f_mode'], options['f_class']))
    gen_runtime_code(options, injectors) # generates runtime fault injector code and insert runtime into a dictionary
    gen_and_write_selector(options) # generates selector file
  
  write_yaml(all_injectors, all_injectors_yaml) # writes runtime into a yaml/storage file
  
  gen_runtime_file(all_injectors) # generate the actual .cpp runtime file

def del_injector(name, injector_type):
  all_injectors = read_input_yaml(all_injectors_yaml)
  injectors = all_injectors[injector_type]
  
  if name in injectors:
    del_selectors([injectors[name]['selectorfilename']])
    del injectors[name]
  else:
    print('Error: %s is not a %s injector!' % (name, injector_type), file = sys.stderr)
    exit(1)
  
  write_yaml(all_injectors, all_injectors_yaml)
  
  gen_runtime_file(all_injectors)
  
def del_injectors(injector_type):
  all_injectors = read_input_yaml(all_injectors_yaml)
  injectors = all_injectors[injector_type]
  
  selectorfilenames = []
  for _, value in injectors.items():
    selectorfilenames.append(value['selectorfilename'])
  del_selectors(selectorfilenames)
  
  all_injectors[injector_type] = {}
  write_yaml(all_injectors, all_injectors_yaml)
  
  gen_runtime_file(all_injectors)

################################################################################

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = 'Error: ' + msg
    print(msg, file = sys.stderr)
  print(__doc__ % globals(), file = sys.stderr)
  sys.exit(retval)

def parse_args(args):
  option = None
  name = None
  
  if len(args) == 0:
    usage()
  elif len(args) == 1:
    option = args[0]
  elif len(args) == 2:
    option = args[0]
    name = args[1]
  else:
    usage('Invalid Input!')
    
  return (option, name)

def main(args):
  option, name = parse_args(args)
  if option == '-r':
    if name == 'custom' or name == 'default':
      print('Deleting all %s injectors!' % (name))
      del_injectors(name)
    else:
      print('Deleting %s' % (name))
      del_injector(name, 'custom')
      
  elif option == '-l':
    if name == 'custom' or name == 'default':
      print('Current %s FIDL software fault injectors:' % (name))
      list_injectors(name)
    else:
      usage('%s is not a valid injector type!' % (name))
      
  elif option == '-a':
    if name == 'default':
      #TODO
      filename = 'tests/test_config.yaml'
      add_injectors(filename, name)
      
      #add_injectors(default_failures_yaml, name)
    else: 
      add_injectors(name, 'custom')
    print('Injector module(s) created.')
  elif option == '-h':
    usage()
  else:
    usage('%s is not a valid option!' % (option))

if __name__ == '__main__':
  main(sys.argv[1:])

