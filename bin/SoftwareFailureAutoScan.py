#! /usr/bin/env python3

"""
%(prog)s takes a single IR file as input and scan all instructions to find potential applicable target points for fault injection, and to create applicable failure modes list.

Usage: %(prog)s [OPTIONS] <source IR file>

List of options:

-outputfilename=<filename>: set the name of the file that stores the list of applicable software failures (default: llfi.applicable.software.failures.txt)
 Note: If <filename> is a relative path instead of an absolute path, the base path of <filename> will be the path of the targeting IR file instead of the calling path.
 
-numOfRuns <number of runs>: set the number of runs for each found failure mode (default: 1)
--enable_tracing: enable tracing
--enable_forward_injection: enable injection on the forward slice of the selected injection point
--enable_backward_injection: enable injection on the backward slice of the selected injection point

"""

# this script creates a text file ; Applicable-Failure-Modes.txt


import os
import subprocess
import sys
from subprocess import call
import yaml

script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths


optbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/opt")
llcbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llc")
llfipasses = os.path.join(script_path, "../llvm_passes/llfi-passes.so")
llfilinklib = os.path.join(script_path, "../runtime_lib")
prog = os.path.basename(sys.argv[0])
# option list for AutoScan pass
options = []
# output file name of AutoScan pass
filename = "llfi.applicable.software.failures.txt"
# directory of the target IR
basedir = ""
# input.yaml generation
run_num_dict = {'numOfRuns': 1}
tracing_dict = {'tracingPropagation':False, 'tracingPropagationOption':{'generateCDFG':False}}
trace_injection_dict = {'includeInjectionTrace':[]}

def parseArgs(args):
   global basedir
   global options
   global filename
   
   cwd = os.getcwd()
   for i, arg in enumerate(args):
       option = arg
       if os.path.isfile(arg):
           basedir = os.path.realpath(os.path.dirname(arg))
           option = os.path.basename(arg)
           options.append(option)
       elif arg.startswith('-outputfilename='):
           filename = arg.split('-outputfilename=')[-1]
           options.append('-softwarescan_outputfilename='+filename)
       elif arg == "-numOfRuns":
           run_num_dict['numOfRuns'] = int(args[i+1])
       elif arg == "--enable_tracing":
           tracing_dict['tracingPropagation'] = True
           tracing_dict['tracingPropagationOption']['generateCDFG'] = True
       elif arg == "--enable_backward_injection":
           trace_injection_dict['includeInjectionTrace'].append('forward')
       elif arg == "--enable_forward_injection":
           trace_injection_dict['includeInjectionTrace'].append('backward')
   os.chdir(basedir)

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = "ERROR: " + msg
    print(msg, file=sys.stderr)
  print(__doc__ % globals(), file=sys.stderr)
  sys.exit(retval)

def runAutoScan(args):
    global filename
    execlist = [optbin , "-load", llfipasses, "-SoftwareFailureAutoScanPass", "-analyze"]
    execlist.extend(args)
    print(' '.join(execlist))
    p = subprocess.Popen(execlist)
    p.wait()
    if p.returncode != 0:
        print("ERROR: Software Auto scan pass return code !=0\n")
        exit(p.returncode)
    elif os.path.isfile(os.path.join(basedir, filename)) == False:
        print("ERROR: No output file found at: "+os.path.join(basedir, filename)+"!\n")
        exit(1)
    return 0

def generateInputYaml():
    global filename
    selector_list = []
    with open(os.path.join(basedir, filename)) as f:
        for line in f.readlines():
            selector_list.append(line.strip())
    customInstselector_dict = {'customInstselector':{'include':selector_list}}
    yaml_dict = {
                    'compileOption':{
                        'instSelMethod':[customInstselector_dict],
                        'regSelMethod':'customregselector',
                        'customRegSelector':'Automatic',
                        },
                    'runOption':[{
                        'run':{
                            'fi_type':'AutoInjection'
                        }
                    }]
                }
    yaml_dict['compileOption'].update(tracing_dict)
    yaml_dict['compileOption'].update(trace_injection_dict)
    yaml_dict['runOption'][0]['run'].update(run_num_dict)
    yaml_text = yaml.dump(yaml_dict, default_flow_style=False)
    with open(os.path.join(basedir, 'input.yaml'), 'w') as f:
        f.write(yaml_text)
    return 0


def main(args):
    parseArgs(args)
    r = runAutoScan(options)
    s = generateInputYaml()
    return 0

if __name__ == "__main__":
        if len(sys.argv[1:]) < 1 or sys.argv[1] == '--help' or sys.argv[1] == '-h':
                usage()
                sys.exit(0)
        r = main(sys.argv[1:])
        sys.exit(r)
