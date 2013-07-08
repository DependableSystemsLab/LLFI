#!/usr/bin/python

#currently, the c file needs to be in the same directory as the script
#basedir is actually the directory with the script and c file
#curdir is where the compilation and execution files will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilib,llfilinklib, and basedir to match your system


import sys
import os
import getopt
import time
import random
import signal
import subprocess
import shutil

optbin = "/data/llvm-2.9/Debug+Asserts/bin/opt"
llcbin = "/data/llvm-2.9/Debug+Asserts/bin/llc"
llvmgcc = "/data/llvm-gcc/bin/llvm-gcc"
llfilib = "/data/llvm-2.9/Release/lib/LLFI.so"
llfilinklib = "/data/LLFI-experimental-master/lib"
optionlist = []
timeout = 500

#config is now executed after main
################################################################################
def config():
	global inputProg,progbin,outputdir,basedir,errordir
	#basedir = "/home/jshwei/Desktop/splash_time_automated"
	# config
	basedir = "/data/CHO"
	currdir = basedir + "/"+inputProg
	progbin = currdir + "/"+inputProg
	
	

	#linkbin = "/data/llvm-2.9/Debug+Asserts/bin/llvm-link"
	#llibin = "/data/llvm-2.9/Debug+Asserts/bin/lli"
	#profilell = basedir + "/../lib/profiling_lib.ll"
	#fill = basedir + "/../lib/fi_random.ll"
	
	outputdir = currdir + "/prog_output"
	basedir = currdir + "/baseline"
	errordir = currdir + "/error_output"

	if not os.path.isdir(currdir):
		os.mkdir(currdir)
	if not os.path.isdir(outputdir):
		os.mkdir(outputdir)
	if not os.path.isdir(basedir):
		os.mkdir(basedir)
	if not os.path.isdir(errordir):
		os.mkdir(errordir)

################################################################################
def execute( execlist):
	#print "Begin"
	#inputFile = open(inputfile, "r")
  global outputfile
  print ' '.join(execlist)
  #print outputfile
  p = subprocess.Popen(execlist, stdout = subprocess.PIPE)
  elapsetime = 0
  while (elapsetime < timeout):
    elapsetime += 1
    time.sleep(1)
    #print p.poll()
    if p.poll() is not None:
      print "\t program finish", p.returncode
      print "\t time taken", elapsetime
      outputFile = open(outputfile, "w")
      outputFile.write(p.communicate()[0])
      outputFile.close()
      #inputFile.close()
      return str(p.returncode)
  #inputFile.close()
  print "\tParent : Child timed out. Cleaning up ... " 
  p.kill()
  return "timed-out"
	#should never go here	
  sys.exit(syscode)
################################################################################

def execCompilation( execlist):
	print ' '.join(execlist)
	p = subprocess.Popen(execlist)
	p.wait()

################################################################################

def compileProg():
	global proffile, fifile, mem2regfile, inputProg,progbin
	inputllfile = progbin + ".ll"
	mem2regfile = progbin + "-mem2reg.ll"
	mem2reg2file = progbin + "-mem2reg2.ll"
	proffile = progbin + "-prof.ll"
	fifile = progbin + "-fi.ll"

	###Instruction selection method
	while 1:
		userInput = raw_input("\nInject faults by ... \n1)Instruction type\n2)Custom instruction selector\n")
		if userInput == '1':
			compileOptions = ['-insttype']
			break
		elif userInput == '2':
			compileOptions = ['-custominstselector']
			break
		else:
			print ("\n\nERROR. Please select one of the presented options\n")


	if userInput == '1':
		#include list
		print ("\nWhich instructions should faults be injected to (ie. all,br,ret)\
														\nPlease enter one at a time. Press Return on empty line to proceed.\n")
		while 1:
			userInput = raw_input("")
			if userInput=='':
				break
			else:
				compileOptions.append('-includeinst='+userInput)

		print ("\nWhich instructions should NOT faults be injected to (ie. all,br,ret)\
														\nPlease enter one at a time. Press Return on empty line to proceed.\n")
		#exclude list
		while 1:
			userInput = raw_input("")
			if userInput=='':
				break
			else:
				compileOptions.append('-excludeinst='+userInput)
	elif userInput =='2':
		userInput = raw_input("Please enter the name of the custom instruction selector (ie. onlymain)\n")
		compileOptions.append('-fiinstselectorname='+userInput)
	###Register selection method
	while 1:
		userInput = raw_input("\nInject faults by ... \n1)Register location\n2)Custom registor selector\n")
		if userInput == '1':
			compileOptions.append('-regloc')
			break
		elif userInput == '2':
			compileOptions.append('-customregselector')
			break
		else:
			print ("\n\nERROR. Please select one of the presented options\n")

	if userInput == '1':
		#register location
		print ("\nWhich register should faults be injected to (ie. dstreg/allsrcreg/srcreg1)\n")
		while 1:
			userInput = raw_input("")
			if userInput=='':
				print("ERROR, Please enter the target register");
			else:
				compileOptions.append('-'+userInput)
				break
	elif userInput =='2':
		userInput = raw_input("Please enter the name of the custom register selector (ie. onlyconstint)\n")
		compileOptions.append('-firegselectorname='+userInput)

	###Trace selection 
	while 1:
		userInput = raw_input("\nSelect trace method ... \n1)Forward\n2)Backward\n")
		if userInput == '1':
			compileOptions.append('-includeforwardtrace')
			break
		elif userInput == '2':
			compileOptions.append('-includebackwardtrace')
			break
		elif userInput == '':
			break
		else:
			print ("\n\nERROR. Please select one of the presented options\n")

  #TODO -S needs to be an option
	execlist = [llvmgcc,'-emit-llvm','-S', '-o', inputllfile, inputProg + '.c']
	execCompilation(execlist)
	execlist = [optbin, "-mem2reg", '-S', '-o', mem2regfile, inputllfile]
	execCompilation(execlist)
	

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
def main():
	config()
  #clear previous output
	global run_number, optionlist, outputfile, proffile, fifile
		
	compileProg()
	#TEMP
	exit(1)
	# baseline
	outputfile = basedir + "/golden_output"
	execlist = [ proffile + '.exe']
	execlist.extend(optionlist)
	execute(execlist)
	# fault injection
	for index in range(0, run_number):
		outputfile = outputdir + "/outputfile-" + str(index)
		errorfile = errordir + "/errorfile-" + str(index)
		execlist = [fifile + '.exe']
		execlist.extend(optionlist)
		ret = execute(execlist)
		if ret == "timed-out":
			error_File = open(errorfile, 'w')
			error_File.write("Program hang\n")
			error_File.close()
		elif int(ret) < 0:
			error_File = open(errorfile, 'w')
			error_File.write("Program crashed, terminated by the system, return code " + ret + '\n')
			error_File.close()
		elif int(ret) > 0:
			error_File = open(errorfile, 'w')
			error_File.write("Program crashed, terminated by itself, return code " + ret + '\n')
			error_File.close()
if __name__=="__main__":
  global run_number, inputProg
  assert len(sys.argv) == 3 and "Format: prog fi_number"
  cfile = sys.argv[1]
  inputProg = cfile.split('.')[0]#the name of input program
  run_number = int(sys.argv[2])
  main()
