#! /usr/bin/env python3

"""
%(prog)s takes a single IR file as input and scan all instructions to find potential applicable target points for fault injection, and to create applicable failure modes list.

Usage: %(prog)s <source IR file>

"""

# this script creates a text file ; Applicable-Failure-Modes.txt


import os
import subprocess
import sys
from subprocess import call

script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths


optbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/opt")
llcbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llc")
llfipasses = os.path.join(llvm_paths.LLVM_DST_ROOT, "../llfi/llvm_passes/llfi-passes.so")
llfilinklib = os.path.join(script_path, "../runtime_lib")
prog = os.path.basename(sys.argv[0])


path = "../test_programs/"

retval = os.getcwd()
AutoDisPath = os.path.join(retval, "Auto-Discovery")
if not os.path.exists(AutoDisPath):
	os.makedirs("Auto-Discovery")
customfaillist = os.path.join(AutoDisPath, "Custom-Failure-List.txt")
applifailmodes = os.path.join(AutoDisPath, "Applicable-Failure-Modes.txt")

def main(programroot):

	tempPath = os.path.abspath(programroot)
	os.chdir(AutoDisPath)
     	
	result = subprocess.check_output([optbin , "-load", llfipasses, "-AutoScan_Pass", tempPath])

       
	with open(customfaillist) as result:	
		uniqlines = set(result.readlines())
		with open(applifailmodes, 'w') as rmdup:
		    rmdup.writelines(set(uniqlines))

	myfile=customfaillist
	## if file exists, delete it ##
	if os.path.isfile(myfile):
		os.remove(myfile)
	else:    ## Show an error ##
		print("Error: %s file not found" % myfile)

if __name__=="__main__":
  main(sys.argv[1])
