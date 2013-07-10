#!/usr/bin/python

#currently, the c file(s) needs to be in the same directory as the script
#basedir is actually the directory with the script and c file(s)
#curdir is where the compilation and execution files will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilib,llfilinklib, and basedir to match your system
# sys.path.append() a path that points to your local yaml library

import sys
sys.path.append('/ubc/ece/home/ugrads/a/a7q7/.local/lib/python2.6')
sys.path.append('/ubc/ece/home/ugrads/a/a7q7/extra/llfi/bin')
from traceDiff import *
import glob
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

optbin = "/ubc/ece/home/kp/ugrads/a7q7/llvm/Release/bin/opt"
llcbin = "/ubc/ece/home/kp/ugrads/a7q7/llvm/Release/bin/llc"
llvmlink = "/ubc/ece/home/kp/ugrads/a7q7/llvm/Release/bin/llvm-link"
llvmgcc = "/ubc/ece/home/kp/ugrads/a7q7/llvmgcc/bin/llvm-gcc"
llfilib = "/ubc/ece/home/kp/ugrads/a7q7/llvm/Release/lib/LLFI.so"
llfilinklib = "/ubc/ece/home/kp/ugrads/a7q7/llfi/lib"
llfiTDbin = "python /ubc/ece/home/kp/ugrads/a7q7/llfi/bin/traceDiff.py"
optionlist = []
timeout = 500

with open('input.yaml','r') as f:
	doc = yaml.load(f)

maxTraceCount = 0

#config is now executed after main
################################################################################
def config():
	global inputProg,progbin,inputdir,outputdir,basedir,errordir
	#basedir = "/home/jshwei/Desktop/splash_time_automated"
	# config
	basedir = os.path.dirname(os.path.abspath(__file__)) #path of directory where script is running on
	currdir = basedir + "/"+inputProg
	progbin = currdir + "/"+inputProg
	

	#linkbin = "/extra/llvm/Release/bin/llvm-link"
	#llibin = "/extra/llvm/Release/bin/lli"
	#profilell = basedir + "/../lib/profiling_lib.ll"
	#fill = basedir + "/../lib/fi_random.ll"
	
	inputdir = currdir + "/prog_input"
	outputdir = currdir + "/prog_output"
	basedir = currdir + "/baseline"
	errordir = currdir + "/error_output"

	print currdir, inputdir, outputdir, basedir, errordir
	if not os.path.isdir(currdir):
		os.mkdir(currdir)
	if not os.path.isdir(inputdir):
		os.mkdir(inputdir)
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
  #get state of directory
  dirSnapshot()
  p = subprocess.Popen(execlist, stdout = subprocess.PIPE)
  elapsetime = 0
  while (elapsetime < timeout):
    elapsetime += 1
    time.sleep(1)
    #print p.poll()
    if p.poll() is not None:
      moveOutput()
      print "\t program finish", p.returncode
      print "\t time taken", elapsetime
      outputFile = open(outputfile, "w")
      outputFile.write(p.communicate()[0])
      outputFile.close()
      replenishInput() #for cases where program deletes input or alters them each run
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
	p = subprocess.Popen(execlist, stdout=subprocess.PIPE)

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
	inputllfile = progbin + ".ll"
	mem2regfile = progbin + "-mem2reg.ll"
	mem2reg2file = progbin + "-mem2reg2.ll"
	proffile = progbin + "-prof.ll"
	proftracedfile = progbin + "-proft.ll"
	fifile = progbin + "-fi.ll"
	finjfile = progbin + "-finj.ll"
	goldTraceLL = progbin + "-gt.ll"
	faultTraceLL = progbin + "-ft.ll"

	#Loop through directory for all c, cc, cpp files
	srcFiles = [ each for each in os.listdir('.') if each.endswith('.c') or each.endswith('.cc') or each.endswith('.cpp')] 

  #TODO -S needs to be an option
	if len(srcFiles) ==1:
		execlist = [llvmgcc,'-emit-llvm','-S', '-o', inputllfile, srcFiles[0]]
		execCompilation(execlist)
	elif len(srcFiles) >1:
		for  ii, src in enumerate(srcFiles):
			execlist = [llvmgcc,'-emit-llvm','-S', '-o', progbin +str(ii)+".ll", src]
			execCompilation(execlist)
		execlist = [llvmlink, '-S','-o',inputllfile]
		for ii, src in enumerate(srcFiles):
			execlist.append(progbin+str(ii)+".ll")
		execCompilation(execlist)

	execlist = [optbin, "-mem2reg", '-S', '-o', mem2regfile, inputllfile]
	execCompilation(execlist)
	

	execlist = [optbin, '-load', llfilib, '-S', '-genllfiindexpass', '-o',mem2reg2file, mem2regfile]
	execCompilation(execlist)
	
	execlist = [optbin, '-load', llfilib, '-profilingpass','-instTrace', '-tout', 'goldTraceOutput', '-S']
	execlist2 = ['-o', proffile, mem2reg2file]
	execlist.extend(compileOptions)
	execlist.extend(execlist2)
	execCompilation(execlist)

	execlist = [optbin, '-load', llfilib, "-faultinjectionpass",'-instTrace', \
	'-tout', 'faultyTraceOutput', '-S']
	if (maxTraceCount > 0):
		execlist3 = ['-maxTrace', str(maxTraceCount)]
		execlist.extend(execlist3)
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
def readCycles():
	global totalcycles
	profinput= open("llfi.stat.prof.txt")
	while 1:
		line = profinput.readline()
		if line.strip():
			if line[0] == 't':
				label, totalcycles = line.split("=")
				break
################################################################################
def storeInputFiles():
	global inputList
	inputList=[]
	for opt in optionlist:
		if os.path.isfile(opt):#stores all files in inputList and copy over to inputdir
			shutil.copy2(opt, inputdir+'/'+opt)
			inputList.append(opt)

################################################################################
def replenishInput():
	for each in inputList:
		if not os.path.isfile(each):#copy deleted inputfiles back to basedir
			shutil.copy2(inputdir+'/'+each,each)################################################################################
def moveOutput():
	for each in[file for file in os.listdir(".")]:
		if each not in dirBefore and each !="llfi.stat.prof.txt":
			flds = each.split(".")
			newName = '.'.join(flds[0:-1])
			newName+='.'+run_id+'.'+flds[-1]
			os.rename(each,outputdir+'/'+newName)
################################################################################
def dirSnapshot():
	global dirBefore
	dirBefore=[]
	for each in[file for file in os.listdir(".")]:
		dirBefore.append(each)

################################################################################
def main():
	config()
  #clear previous output
	global optionlist, outputfile, proffile, fifile, totalcycles,inputList,run_id
	readCompileOption()
	compileProg()
	storeInputFiles()
	# baseline
	outputfile = basedir + "/golden_output"
	execlist = [ progbin + "-prof.ll" + '.exe']#TODO change back to proffile 
	execlist.extend(optionlist)
	run_id=''#execute requires run_id to be defined
	execute(execlist)

	# get total num of cycles
	readCycles()

	#Setup each config file and it's corresponding run_number
	rOpt = doc["runOption"]
	for ii, run in enumerate(rOpt):
		if "numOfRuns" not in run["run"]:
			print ("ERROR in input.yaml. Must include a run number per fi config.")
			exit(1)
		else:
			run_number=run["run"]["numOfRuns"]
			#write new fi config file according to input.yaml
			fi_type=fi_cycle=fi_index=fi_reg_index=fi_bit=''
			if "fi_type" in run["run"]:
				fi_type=run["run"]["fi_type"]
			if "fi_cycle" in run["run"]:
				fi_cycle=run["run"]["fi_cycle"]
			if "fi_index" in run["run"]:
				fi_index=run["run"]["fi_index"]			
			if "fi_reg_index" in run["run"]:
				fi_reg_index=run["run"]["fi_reg_index"]		
			if "fi_bit" in run["run"]:
				fi_bit=run["run"]["fi_bit"]

			# fault injection
			for index in range(0, run_number):
				run_id = str(ii)+"-"+str(index)
				outputfile = outputdir + "/outputfile-" + "run-"+run_id
				errorfile = errordir + "/errorfile-" + "run-"+run_id
				execlist = [progbin + "-fi.ll" + '.exe']#TODO change back to fifile
	
				ficonfig_File = open("llfi.config.fi.txt", 'w')
				
				if fi_type:
					ficonfig_File.write("fi_type="+fi_type+'\n')
				if fi_cycle:
					pass#Do nothing, fi_cycle is already storing user input specific cycle
				else:
					fi_cycle=random.randint(1, int(totalcycles))#randomly choose cycle if it isnt specified
				ficonfig_File.write("fi_cycle="+str(fi_cycle)+'\n')
				if fi_index:
					ficonfig_File.write("fi_index="+str(fi_index)+'\n')
				if fi_reg_index:				
					ficonfig_File.write("fi_reg_index="+str(fi_reg_index)+'\n')
				if fi_bit:				
					ficonfig_File.write("fi_bit="+str(fi_bit)+'\n')

				ficonfig_File.close()
			
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

	#Post LLFI Runs;
	#print glob.glob("./main/prog_output/.[0-9]-[0-9].faultyTraceOutput")
	for faultyOutput in glob.glob("./main/prog_output/.[0-9]-[0-9].faultyTraceOutput"):
		index = faultyOutput[20:23]
		#print faultyOutput
		#print index
		
		origFile = './main/prog_output/..goldTraceOutput'
		newFile = faultyOutput
		outPutFile = './main/prog_output/.'+index+'.traceDiffReport'
		args = ["null", origFile, newFile]
		traceDiff(args, outPutFile)

		#execlist = [llfiTDbin, './main/prog_output/..goldTraceOutput', faultyOutput,
		#						'>', './main/prog_output/.'+index+'.traceDiffReport']
		#
		#print execlist 
		#execCompilation(execlist)

################################################################################

if __name__=="__main__":
  global inputProg
  inputProg = doc["setUp"]["targetDirectoryName"]#the name of input program
  for ii,arg in enumerate(sys.argv):
    if ii: #add all commandline arguments to optionlist except the first one which is the this script's name
      optionlist.append(arg)
  main()
