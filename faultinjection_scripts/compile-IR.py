#!/usr/bin/python

#The c file(s) needs to be in the same directory as the script, or
#be in directories under the current one. 

#If the source files are stored in multiple directories and uses a 
#common directory for .h library files. Put name that library folder
#"include" for this script to work

#basedir is actually the directory with the script and c file(s)
#curdir is where the compilation files and executables will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilink to match your system, 
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
llvmlink = "/data/llvm-2.9/Debug+Asserts/bin/llvm-link"
llvmgcc = "/data/llvm-gcc/bin/llvm-gcc"

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
def compileProg():
	global  mem2regfile,progbin,compileOptions
	inputllfile = progbin + ".ll"
	mem2regfile = progbin + "-mem2reg.ll"


	#Loop through directory for all c, cc, cpp files
	srcFiles = []
	for path, subdirs, files in os.walk('.'):
		if inputProg in subdirs:
			subdirs.remove(inputProg)
		for each in files:
			if each.lower().endswith('.c') or each.lower().endswith('.cc') or each.lower().endswith('.cpp'):
				srcFiles.append(os.path.join(path,each)) 
	print "Source files to be compiled: "
	print srcFiles
	print "\n======Compile======"

  #TODO -S needs to be an option
	if len(srcFiles) ==1:
		execlist = [llvmgcc,'-w','-I.','-emit-llvm','-S', '-o', inputllfile, srcFiles[0]]
		execCompilation(execlist)
	elif len(srcFiles) >1:
		#llvmgcc for each .c file
		for  ii, src in enumerate(srcFiles):
			execlist = [llvmgcc,'-w','-I.','-Iinclude']
			srcDir = src.split('/')[-2]#-1 is the src file itself
			execlist.append('-I'+srcDir)
			execlist.extend(['-emit-llvm','-S', '-o', progbin +str(ii)+".ll", src])
			execCompilation(execlist)
		execlist = [llvmlink, '-S','-o',inputllfile]
		#building llvmlink command
		for ii, src in enumerate(srcFiles):
			execlist.append(progbin+str(ii)+".ll")
		execCompilation(execlist)

	execlist = [optbin, "-mem2reg", '-S', '-o', mem2regfile, inputllfile]
	execCompilation(execlist)

################################################################################
def checkSuccess():
	print "\n"
	if not os.path.isfile(mem2regfile):
		print "There's an error with compiling the IR file. Please refer to the ReadMe or compile the IR file on your own."
	else:
		IR_lastModified = str(os.path.getmtime(mem2regfile))
		if IR_lastModified<initTime:
			print "There's an error with compiling the IR file. Please refer to the ReadMe or compile the IR file on your own."
		else:
			print "IR file successfully generated"
	print "\n"

################################################################################
def main():

	config()
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
