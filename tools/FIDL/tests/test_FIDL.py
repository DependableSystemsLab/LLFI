#! /usr/bin/env python3

"""
Tests the FIDL algorithm.


-a:    adds FIDL test cases
-r:    removes FIDL test cases
-t:    executes tests
-h:    shows help

Steps:
1. Execute with -a
2. Build LLFI
3. Execute this script where LLFI was built -t
4. Execute -r & rebuild LLFI to get rid of test cases

Run this file *after* successfully executing the llfi regression test
"""

import sys, os, subprocess, shutil
import yaml
from distutils.dir_util import copy_tree

script_path = os.path.realpath(os.path.dirname(__file__))

test_config_path = os.path.join(script_path, 'test_config.yaml')
fidl_al_path = os.path.join(script_path, '../FIDL-Algorithm.py')

fidl_config_dir = os.path.join(script_path, 'fidl_config/')
fidl_tests_dir = os.path.join(script_path, 'fidl_test/')

def execute_tests():
  global doc
  
  # delete and create a new tests folder
  del_mkdir(fidl_tests_dir)
  
  # create folder for each test case
  for n in doc['tests']:
    dir_name = n['FIDL']['Failure_Mode']
    dir_path = os.path.join(fidl_tests_dir, dir_name)
    os.makedirs(dir_path)
    print('Testing %s' % dir_name)
    
    l = [['Expected', n['config']['simulate']], [['Output', extract_names(n)[1]]]]
    for i in l:
      # create inner directory and cd to it
      inner_dir_path = os.path.join(dir_path, i[0])
      os.makedirs(inner_dir_path)
      os.chdir(inner_dir_path)
      
      # creates the input.yaml
      dump_yaml(os.path.join(innder_dir_path, 'input.yaml'), create_input_yaml(n, i[1]))
      
      # copy in the program
      copy_tree(os.path.join(script_path, n['config']['program']), inner_dir_path)
      
      # instrument
      
      # profile
      
      # fault injection
      
      # check result
    
def create_input_yaml(test, selector):
  global doc
  
  template = doc['inputTemplate'].copy()
  template['compileOption']['instSelMethod'][0]['customInstselector']['include'] = [selector]
    
  template['runOption'][0]['run']['fi_cycle'] = test['config']['fi_cycle']
  template['runOption'][0]['run']['fi_index'] = test['config']['fi_index']
    
  return template

def del_mkdir(dir_path):
  if os.path.exists(dir_path):
    shutil.rmtree(dir_path)
  os.makedirs(dir_path)
  
def extract_names(test):
  f_mode = test['FIDL']['Failure_Mode']
  f_class = test['FIDL']['Failure_Class']
  
  filename = '%s.yaml' % f_mode
  name = '%s(%s)' % (f_mode, f_class)
  
  return (filename, name)
  
def dump_yaml(path, yaml_object):
  f = open(path, 'w')
  f.write(yaml.dump(yaml_object))
  f.close()

def run_fidl_algorithm(add):
  global doc
  
  # delete and create a new fidl script config(s) folder
  if add:
    del_mkdir(fidl_config_dir)
  
  for n in doc['tests']:
    filename, name = extract_names(n)
    
    # create new fidl script from ones specified in test_config.yaml
    filename_path = os.path.join(fidl_config_dir, filename)
    dump_yaml(filename_path, n['FIDL'])
    
    if add:
      option = [fidl_al_path, filename_path]
    else:
      option = [fidl_al_path, '-r', name]
      
    #TODO what is the proper way for this?
    # redirect error and such...
    
    # executes the fidl algorithm on the script
    retVal = subprocess.call(option)
    if retVal != 0:
      print('Error: %s is not a valid fidl script!' % filename)
      exit(1)
     
  # delete fidl script config(s) folder if removing
  if os.path.exists(fidl_config_dir) and not add:
    shutil.rmtree(fidl_config_dir)
    
def remove_tests():
  run_fidl_algorithm(False)

def add_tests():
  run_fidl_algorithm(True)

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = 'ERROR: ' + msg
    print(msg, file = sys.stderr)
  print(__doc__ % globals(), file = sys.stderr)
  sys.exit(retval)

def parse_args(args):
  option = args[0]
  if option == '-a':
    add_tests()
  elif option == '-r':
    remove_tests()
  elif option == '-t':
    execute_tests()
  elif option == '-h':
    usage()
  else:
    usage('Invalid Argument: ' + option)

def read_yaml():
  global doc
  f = open(test_config_path)
  doc = yaml.load(f)
  f.close()

def main(args):
  read_yaml()
  parse_args(args)

if __name__ == '__main__':
  if len(sys.argv) == 1:
    usage('Please specify an option.')
  main(sys.argv[1:])
