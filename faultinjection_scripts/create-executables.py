#!/usr/bin/python

#This script takes an IR file and creates prof.ll.exe and fi.ll.exe from it

#The IR file needs to be contained in a directory specified by targetDirectoryName
#in input.yaml. That directory needs to be in the directory of this script.

#Everytime the contents of compileOption is changed in input.yaml
#this script should be run to create new fi.exe and prof.exe

#basedir is actually the directory with the script and c file(s)
#curdir is where the compilation files and executables will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilib, and llfilinklib to match your system, 
#and also change sys.path.append() to a path that points to your local Pyyaml library

import sys
sys.path.append('/ubc/ece/home/kp/ugrads/v7c7/lib/python/')
import yaml
import os
import re
import getopt
import time
import random
import signal
import subprocess
import shutil
import random

optbin = "/data/llvm-2.9/Debug+Asserts/bin/opt"
llcbin = "/data/llvm-2.9/Debug+Asserts/bin/llc"
llvmgcc = "/data/llvm-gcc/bin/llvm-gcc"
llfilib = "/data/llvm-2.9/Release/lib/LLFI.so"
llfilinklib = "/data/LLFI-experimental-master/lib"


#Check for input.yaml's presence
try:
	f = open('input.yaml','r')
except:
	print "ERROR. No input.yaml file in the current directory."
	exit(1)


#Check for input.yaml's correct formmating
try:
	doc = yaml.load(f)
	f.close()
except:
	print "Error. input.yaml is not formatted in proper YAML (reminder: use spaces, not tabs)"
	exit(1)

#Check for compileOption in input.yaml
try:
	cOpt = doc["compileOption"]
except:
	print "ERROR in input.yaml. Please include compileOptions."
	exit(1)

#Just a little tweak to make the output look less clustered
print "\n"	

################################################################################
def config():
	global inputProg,progbin
	# config
	basedir = os.path.dirname(os.path.abspath(__file__)) #path of directory where script is running on
	currdir = basedir + "/"+inputProg
	progbin = currdir + "/"+inputProg

	if not os.path.isdir(currdir):
		os.mkdir(currdir)
		
################################################################################
def execCompilation( execlist):
	print ' '.join(execlist)
	p = subprocess.Popen(execlist)
	p.wait()

################################################################################
def readCompileOption():
	global compileOptions
	
	###Instruction selection method
	if "instSelMethod" not in cOpt:	
		print ("\n\nERROR in input.yaml. Please include an 'instSelMethod' key value pair under compileOption.\n")
		exit(1)
	else:
		#Select by instruction type
		if cOpt["instSelMethod"] == 'insttype':
			compileOptions = ['-insttype']
			if "include" not in cOpt:	
				print ("\n\nERROR in input.yaml. An 'Include' list must be present for the insttype method.\n")
				exit(1)
			else:
				#include list
				for inst in cOpt["include"]:
					compileOptions.append('-includeinst='+inst)
				#exclude list
				if "exclude" in cOpt:
					for inst in cOpt["exclude"]:
						compileOptions.append('-excludeinst='+inst)
		#Select by custom instruction 
		elif cOpt["instSelMethod"] == 'custominstselector':
			compileOptions = ['-custominstselector']
		
			if "customInstSelector" not in cOpt:	
				print ("\n\nERROR in input.yaml. A 'customInstSelector' key value pair must be present for the customeinstselector method.\n")
				exit(1)
			else:
				compileOptions.append('-fiinstselectorname='+cOpt["customInstSelector"])

		else:
			print ("\n\nERROR in input.yaml. Unknown Instruction selection method.\n")
			exit(1)

	
	###Register selection method
	if "regSelMethod" not in cOpt:	
		print ("\n\nERROR in input.yaml. Please include an 'regSelMethod' key value pair under compileOption.\n")
		exit(1)
	else:
		#Select by register location
		if cOpt["regSelMethod"] == 'regloc':
			compileOptions.append('-regloc')
			if "regloc" not in cOpt:	
				print ("\n\nERROR in input.yaml. An 'regloc' key value pair must be present for the regloc method.\n")
				exit(1)
			else:
				compileOptions.append('-'+cOpt["regloc"])

		#Select by custom register
		elif cOpt["regSelMethod"]  == 'customregselector':
			compileOptions.append('-customregselector')
			if "customRegSelector" not in cOpt:	
				print ("\n\nERROR in input.yaml. An 'customRegSelector' key value pair must be present for the customregselector method.\n")
				exit(1)
			else:
					compileOptions.append('-firegselectorname='+cOpt["customRegSelector"])

		else:
			print ("\n\nERROR in input.yaml. Unknown Register selection method.\n")
			exit(1)

	###Trace selection 
	if "trace" in cOpt:
		for trace in cOpt["trace"]:
			if trace == 'forward':
				compileOptions.append('-includeforwardtrace')
			elif trace == 'backward':
				compileOptions.append('-includebackwardtrace')
			else:
				print ("\n\nERROR in input.yaml. Invalid value for trace. (forward/backward allowed)\n")
				exit(1)

################################################################################
def compileProg():
	global proffile, fifile, mem2regfile,progbin,compileOptions
	mem2regfile = progbin + "-mem2reg.ll"
	mem2reg2file = progbin + "-mem2reg2.ll"
	proffile = progbin + "-prof.ll"
	fifile = progbin + "-fi.ll"
	
	if not os.path.isfile(mem2regfile):
		print "Error. Cannot find the file - "+mem2regfile
		print "Please try running compile-IR.py. Or build the IR file yourself.\n"
		exit(1)


	execlist = [optbin, '-load', llfilib, '-genllfiindexpass', '-o',mem2reg2file, mem2regfile]
	execCompilation(execlist)
	
	execlist = [optbin, '-load', llfilib, '-profilingpass','-S']
	execlist2 = ['-o', proffile, mem2reg2file]
	execlist.extend(compileOptions)
	execlist.extend(execlist2)
	execCompilation(execlist)

	execlist = [optbin, '-load', llfilib, "-faultinjectionpass",'-S']
	execlist2 = ['-o', fifile, mem2reg2file]
	execlist.extend(compileOptions)
	execlist.extend(execlist2)
	execCompilation(execlist)



	execlist = [llcbin, '-filetype=obj', '-o', proffile + '.o', proffile]
	execCompilation(execlist)
	execlist = [llcbin, '-filetype=obj', '-o', fifile + '.o', fifile]
	execCompilation(execlist)

	execlist = [llvmgcc, '-o', proffile + '.exe', proffile + '.o', '-L'+llfilinklib , '-lllfi']
	execCompilation(execlist)
	execlist = [llvmgcc, '-o', fifile + '.exe', fifile + '.o', '-L'+llfilinklib , '-lllfi']
	execCompilation(execlist)

################################################################################
def checkSuccess():
	print "\n"
	if not os.path.isfile(fifile+'.exe'):
		print "There's an error with building the FaulInjection executable. Please refer to the ReadMe."
	elif not os.path.isfile(proffile+'.exe'):
		print "There's an error with building the Profiling executable. Please refer to the ReadMe."

	else:
		FI_lastModified = str(os.path.getmtime(fifile+'.exe'))
		PF_lastModified = str(os.path.getmtime(proffile+'.exe'))
		if FI_lastModified<initTime or PF_lastModified<initTime:
			print "There's an error with creating the executables. Please refer to the ReadMe or compile the IR file on your own."
		else:
			print "Profiling and FaultInjection executables successfully generated"
	print "\n"

################################################################################
def main():

	config()
	readCompileOption()
	compileProg()
	checkSuccess()

################################################################################

if __name__=="__main__":
  global inputProg, initTime

  initTime= time.time()
  try:
    inputProg = doc["setUp"]["targetDirectoryName"]#the name of input program
  except:
    print "ERROR, Please include a targetDirectoryName field in input.yaml. See ReadMe for directions."
    exit(1)

  main()
