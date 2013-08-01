#!/usr/bin/python

#The script needs to be executed in the same directory as the src c files, or
#be the directory of multiple other src directories.

#If the source files are stored in multiple directories and uses a 
#common directory for .h library files. Put name that library folder
#"include" for this script to work

#basedir is actually the src directory with the c file(s)
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

script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths

optbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/opt")
llcbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llc")
llvmlink = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llvm-link")
llvmgcc = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "llvm-gcc")


basedir = os.getcwd()
#Check for input.yaml's presence
try:
	f = open(basedir+'/input.yaml','r')
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
	global  mem2regfile,progbin,compileOptions, inputllfile
	inputllfile = progbin + ".ll"


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

################################################################################
def checkSuccess():
	print "\n"
	if not os.path.isfile(inputllfile):
		print "There's an error with compiling the IR file. Please refer to the ReadMe or compile the IR file on your own."
	else:
		IR_lastModified = str(os.path.getmtime(inputllfile))
		if IR_lastModified<initTime:
			print "There's an error with compiling the IR file. Please refer to the ReadMe or compile the IR file on your own."
		else:
			print "IR file " + inputllfile +" is successfully generated"
	print "\n"

################################################################################
def main():

	config()
	compileProg()
	checkSuccess()
	#print "================================="
	#print "Executing create-executables.py."
	#print "================================="
	#os.system('create-executables.py')#since this is successful, go ahead and do the next step
	
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
