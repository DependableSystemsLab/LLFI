#!/usr/bin/python

#currently, the c file needs to be in the same directory as the script
#basedir is actually the directory with the script and c file
#curdir is where the compilation and execution files will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilib,llfilinklib, and basedir to match your system


import sys
sys.path.append('/ubc/ece/home/kp/ugrads/v7c7/lib/python/')
import yaml
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

with open('input.yaml','r') as f:
	doc = yaml.load(f)

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

def readCompileOption():
	global compileOptions
	cOpt = doc["compileOption"]
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
		if cOpt["trace"] == 'forward':
			compileOptions.append('-includeforwardtrace')
		elif cOpt["trace"] == 'backward':
			compileOptions.append('-includebackwardtrace')
		else:
			print ("\n\nERROR in input.yaml. Invalid value for trace. (forward/backward allowed)\n")
			exit(1)

################################################################################

def compileProg():
	global proffile, fifile, mem2regfile, inputProg,progbin,compileOptions
	inputllfile = progbin + ".ll"
	mem2regfile = progbin + "-mem2reg.ll"
	mem2reg2file = progbin + "-mem2reg2.ll"
	proffile = progbin + "-prof.ll"
	fifile = progbin + "-fi.ll"

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
	global optionlist, outputfile, proffile, fifile
	readCompileOption()
	compileProg()
	
	# baseline
	outputfile = basedir + "/golden_output"
	execlist = [ proffile + '.exe']
	execlist.extend(optionlist)
	execute(execlist)
	
	#Setup each config file and it's corresponding run_number
	rOpt = doc["runOption"]
	for ii, run in enumerate(rOpt):
		if "numOfRuns" not in run["run"]:
			print ("ERROR in input.yaml. Must include a run number per fi config.")
			exit(1)
		else:
			run_number=run["run"]["numOfRuns"]
			#write new fi config file according to input.yaml
			ficonfig_File = open("llfi.config.fi.txt", 'w')
			if "fi_type" in run["run"]:
				fi_type=run["run"]["fi_type"]
				ficonfig_File.write("fi_type="+fi_type+'\n')
			if "fi_cycle" in run["run"]:
				fi_cycle=run["run"]["fi_cycle"]
				ficonfig_File.write("fi_cycle="+str(fi_cycle)+'\n')
			if "fi_index" in run["run"]:
				fi_index=run["run"]["fi_index"]
				ficonfig_File.write("fi_index="+str(fi_index)+'\n')
			if "fi_reg_index" in run["run"]:
				fi_reg_index=run["run"]["fi_reg_index"]
				ficonfig_File.write("fi_reg_index="+str(fi_reg_index)+'\n')
			if "fi_bit" in run["run"]:
				fi_bit=run["run"]["fi_bit"]
				ficonfig_File.write("fi_bit="+str(fi_bit)+'\n')
		
			ficonfig_File.close()			

			# fault injection
			for index in range(0, run_number):
				outputfile = outputdir + "/outputfile-" + "run-"+str(ii)+"-"+str(index)
				errorfile = errordir + "/errorfile-" + "run-"+str(ii)+"-"+str(index)
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
  global inputProg
  assert len(sys.argv) == 2 and "Format: prog fi_number"
  cfile = sys.argv[1]
  inputProg = cfile.split('.')[0]#the name of input program
  main()
