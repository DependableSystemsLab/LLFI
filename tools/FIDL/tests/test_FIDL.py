#! /usr/bin/env python3

"""
This script is DEPRECATED! This was used to initially test if the 38/39 software failures
converted from .cpp format to the FIDL yaml format was working properly.

Tests FIDL-Algorithm.py.

Usage: %(prog)s [OPTIONS]

-a:    adds FIDL test cases
-r:    removes FIDL test cases
-t:    executes tests
-h:    shows help

Steps:
1. Execute with -a in LLFI_SRC
2. Build LLFI
3. Execute this script in LLFI_DST with -t
4. Execute -r in LLFI_SRC and rebuild LLFI to get rid of test cases

Run this file *after* successfully executing the llfi regression test
This tests compares the generated FIDL-Algorithm.py's generated faultinjection.ll and profiling.ll
against the actual faultinjection.ll and profiling.ll from the real selector cpp file.
"""

import sys, os, subprocess, shutil
import yaml
from distutils.dir_util import copy_tree

script_path = os.path.realpath(os.path.dirname(__file__))
prog = os.path.basename(sys.argv[0])

llfiroot = os.path.dirname(os.path.dirname(os.path.dirname(script_dir)))

test_config_path = os.path.join(script_path, 'test_config.yaml')
fidl_al_path = os.path.join(script_path, '../FIDL-Algorithm.py')

programs_dir = os.path.join(llfiroot, 'test_suite/PROGRAMS/')
fidl_config_dir = os.path.join(script_path, 'fidl_config/')
fidl_tests_dir = os.path.join(script_path, 'fidl_test/')

bin_path = os.path.join(script_path, '../../../bin')
instrument_path = os.path.join(bin_path, 'instrument')
profile_path = os.path.join(bin_path, 'profile')
injectfault_path = os.path.join(bin_path, 'injectfault')

ir_ext = '.ll'
expected = 'Expected'
output = 'Output'

def ir_file_equals(ir1_path, ir2_path):
  with open(ir1_path) as f:
    lines1 = f.read().splitlines()
  with open(ir2_path) as f:
    lines2 = f.read().splitlines()
    
  if len(lines1) != len(lines2):
    return False
    
  # check the file content (ignoring the first line where the path
  # of the files will be different
  for i in range(1, len(lines1)):
    if lines1[i] != lines2[i]:
      return False
      
  return True
  
def is_same_result(test_dir_path, program_name):
  file_list = ['llfi/%s-faultinjection%s' % (program_name, ir_ext), 'llfi/%s-profiling%s' % (program_name, ir_ext)]

  # check if the generated ir files are equal
  for n in file_list:
    if not ir_file_equals(os.path.join(test_dir_path, expected, n), os.path.join(test_dir_path, output, n)):
      return False

  return True
  
def execute_tests():
  global doc
  
  # delete and create a new tests folder
  del_mkdir(fidl_tests_dir)
  
  # create folder for each test case
  for n in doc['tests']:
    dir_name, name = extract_names(n)
    dir_path = os.path.join(fidl_tests_dir, dir_name)
    os.makedirs(dir_path)
    print('Testing %s' % dir_name)
    
    program_name = n['config']['program']
    
    l = [[expected, n['config']['simulate']], [output, name]]
    for i in l:
      # create inner directory and cd to it
      inner_dir_path = os.path.join(dir_path, i[0])
      os.makedirs(inner_dir_path)
      os.chdir(inner_dir_path)
      
      # creates the input.yaml
      dump_yaml(os.path.join(inner_dir_path, 'input.yaml'), create_input_yaml(n, i[1]))
      
      # copy in the program
      copy_tree(os.path.join(programs_dir, program_name), inner_dir_path)
      
      # instrument
      execlist = [instrument_path, '--readable', '-lpthread', program_name + ir_ext]
      ret_val = subprocess.call(execlist, stdout = open(os.devnull, 'wb'), stderr = open(os.devnull, 'wb'))
      if (ret_val != 0):
        print('Error: Instrument failed!')
        exit(1)
      
    # check results
    if is_same_result(dir_path, program_name):
      print('Success: %s' % dir_name)
    else:
      print('Error: %s' % dir_name)
    
def create_input_yaml(test, selector):
  global doc
  
  template = doc['inputTemplate'].copy()
  template['compileOption']['instSelMethod'][0]['customInstselector']['include'] = [selector]
    
  return template

def del_mkdir(dir_path):
  if os.path.exists(dir_path):
    shutil.rmtree(dir_path)
  os.makedirs(dir_path)
  
def extract_names(test):
  f_mode = test['FIDL']['Failure_Mode']
  f_class = test['FIDL']['Failure_Class']
  
  filename = '_%s_%s' % (f_class, f_mode)
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
    filename = filename + '.yaml'
    
    # create new fidl script from ones specified in test_config.yaml
    filename_path = os.path.join(fidl_config_dir, filename)
    dump_yaml(filename_path, n['FIDL'])
    
    if add:
      option = [fidl_al_path, '-a', filename_path]
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
  print('This script is DEPRECATED! See -h')
  read_yaml()
  parse_args(args)

if __name__ == '__main__':
  if len(sys.argv) == 1:
    usage('Please specify an option.')
  main(sys.argv[1:])
