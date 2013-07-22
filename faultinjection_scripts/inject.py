#!/usr/bin/python

#This script injects faults the program and produces output

#The fi.ll.exe needs to be contained in a directory specified by targetDirectoryName
#in input.yaml. That directory needs to be in the directory of this script.

#This should be run right after create-executables.py is run to provide
#up-to-date llfi.stat.prof.txt 

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

runOverride = False
optionlist = []
timeout = 500

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
	if "kernelOption" in doc:
		for opt in doc["kernelOption"]:	
			if opt=="forceRun":
				runOverride = True
				print "Kernel: Forcing run"
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
	global inputProg,progbin,inputdir,outputdir,basedir,errordir,stddir,currdir
	# config
	basedir = os.path.dirname(os.path.abspath(__file__)) #path of directory where script is running on
	currdir = basedir + "/"+inputProg
	progbin = currdir + "/"+inputProg

	inputdir = currdir + "/prog_input"
	outputdir = currdir + "/prog_output"
	basedir = currdir + "/baseline"
	errordir = currdir + "/error_output"
	stddir = currdir + "/std_output"

	if not os.path.isdir(currdir):
		os.mkdir(currdir)
	if not os.path.isdir(outputdir):
		os.mkdir(outputdir)
	if not os.path.isdir(basedir):
		os.mkdir(basedir)
	if not os.path.isdir(errordir):
		os.mkdir(errordir)
	if not os.path.isdir(inputdir):
		os.mkdir(inputdir)
	if not os.path.isdir(stddir):
		os.mkdir(stddir)


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
      print "\t time taken", elapsetime,"\n"
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
def storeInputFiles():
	global inputList
	inputList=[]
	for opt in optionlist:
		if os.path.isfile(opt):#stores all files in inputList and copy over to inputdir
			shutil.copy2(opt, inputdir+'/'+opt)
			inputList.append(opt)

################################################################################
def replenishInput():#TODO make condition to skip this if input is present
	for each in inputList:
		if not os.path.isfile(each):#copy deleted inputfiles back to basedir
			shutil.copy2(inputdir+'/'+each,each)

################################################################################
def moveOutput():
	#move all newly created files
	for each in[file for file in os.listdir(".")]:
		if each not in dirBefore:
			flds = each.split(".")
			newName = '.'.join(flds[0:-1])
			newName+='.'+run_id+'.'+flds[-1]
			os.rename(each,outputdir+'/'+newName)

################################################################################
def dirSnapshot():
	#snapshot of directory before each execute() is performed
	global dirBefore
	dirBefore=[]
	for each in[file for file in os.listdir(".")]:
		dirBefore.append(each)

################################################################################
def readCycles():
	global totalcycles
	profinput= open("llfi.stat.prof.txt","r")
	while 1:
		line = profinput.readline()
		if line.strip():
			if line[0] == 't':
				label, totalcycles = line.split("=")
				break
	profinput.close()

################################################################################
def checkValues(key, val, var1 = None,var2 = None,var3 = None,var4 = None):
	#preliminary input checking for fi options
	#also checks for fi_bit usage by non-kernel users
	#optional var# are used for fi_bit's case only
	if key =='run_number':
		assert isinstance(val, int)==True, key+" must be an integer in input.yaml"
		assert int(val)>0, key+" must be greater than 0 in input.yaml"

	elif key == 'fi_type':
		pass

	elif key == 'fi_cycle':
		assert isinstance(val, int)==True, key+" must be an integer in input.yaml"
		assert int(val)>0, key+" must be greater than 0 in input.yaml"
		assert int(val) <= int(totalcycles), key +" must be less than or equal to "+totalcycles.strip()+" in input.yaml"

	elif key == 'fi_index':
		assert isinstance(val, int)==True, key+" must be an integer in input.yaml"
		assert int(val)>0, key+" must be greater than 0 in input.yaml"

	elif key == 'fi_reg_index':
		assert isinstance(val, int)==True, key+" must be an integer in input.yaml"
		assert int(val)>0, key+" must be greater than 0 in input.yaml"

	elif key == 'fi_bit':
		assert isinstance(val, int)==True, key+" must be an integer in input.yaml"
		assert int(val)>0, key+" must be greater than 0 in input.yaml"

		if runOverride:
			pass
		elif var1 > 1 and var2 and var3 and var4:
			user_input = raw_input("\nWARNING. Injecting into the same bit multiple times "+
									"is redundant as it would yield the same result."+
									"\nTo turn off this warning, please see Readme "+
									"for kernel mode.\nDo you wish to continue anyway? (Y/N)\n ")
			if user_input.upper() =="Y":
				pass
			else:
				exit(1)

################################################################################
def main():
	global optionlist, outputfile, totalcycles,run_id	

	config()
	inputllfile = currdir +"/"+llfile
	#fifile is the faultinject executable that has the same name as inputllfile
	fifile = currdir+"/"+llfile[:-3]+"-fi.ll.exe" 

	if not os.path.isfile(inputllfile):
		print "Error. Cannot find the IR file - "+inputllfile
		print "Please try running compile-IR.py. Or build the IR file yourself.\n"
		exit(1)
	
	# get total num of cycles
	readCycles()

	storeInputFiles()

	#Set up each config file and its corresponding run_number
	try:
		rOpt = doc["runOption"]
	except:
		print "ERROR in input.yaml. Please include runOption."
		exit(1)

	if not os.path.isfile(fifile):
		print "Error. The executable "+ fifile+" does not exist."
		print "Please build the executables with create-executables.py.\n"
		exit(1)
	else:
		print "======Fault Injection======"
		for ii, run in enumerate(rOpt):
			print "---FI Config #"+str(ii)+"---"

			if "numOfRuns" not in run["run"]:
				print ("ERROR in input.yaml. Must include a run number per fi config.")
				exit(1)
			else:
				run_number=run["run"]["numOfRuns"]
				checkValues("run_number",run_number)

				#write new fi config file according to input.yaml
				fi_type=fi_cycle=fi_index=fi_reg_index=fi_bit=''
				ficonfig_File = open("llfi.config.fi.txt", 'w')
				if "fi_type" in run["run"]:
					fi_type=run["run"]["fi_type"]
					checkValues("fi_type",fi_type)
					ficonfig_File.write("fi_type="+str(fi_type)+'\n')
				if "fi_cycle" in run["run"]:
					fi_cycle=run["run"]["fi_cycle"]
					checkValues("fi_cycle",fi_cycle)
					ficonfig_File.write("fi_cycle="+str(fi_cycle)+'\n')
				if "fi_index" in run["run"]:
					fi_index=run["run"]["fi_index"]	
					checkValues("fi_index",fi_index)
					ficonfig_File.write("fi_index="+str(fi_index)+'\n')
				if "fi_reg_index" in run["run"]:
					fi_reg_index=run["run"]["fi_reg_index"]	
					checkValues("fi_reg_index",fi_reg_index)
					ficonfig_File.write("fi_reg_index="+str(fi_reg_index)+'\n')	
				if "fi_bit" in run["run"]:
					fi_bit=run["run"]["fi_bit"]
					checkValues("fi_bit",fi_bit,run_number,fi_cycle,fi_index,fi_reg_index)
					ficonfig_File.write("fi_bit="+str(fi_bit)+'\n')
				ficonfig_File.close()

				# fault injection
				for index in range(0, run_number):
					run_id = str(ii)+"-"+str(index)
					outputfile = stddir + "/outputfile-" + "run-"+run_id
					errorfile = errordir + "/errorfile-" + "run-"+run_id
					execlist = [progbin + "-fi.ll" + '.exe']#TODO change back to fifile
	
					if fi_cycle:
						#Do nothing, fi_cycle is already storing user input specific cycle
						pass
					else:
						#Create a new random fi_cycle in llfi.config.fi.txt for each run
						fi_cycle=random.randint(1, int(totalcycles))#randomly choose cycle if it isnt specified
						ficonfig_File = open("llfi.config.fi.txt", 'w')
						ficonfig_File.write("fi_cycle="+str(fi_cycle)+'\n')
						if fi_type:
							ficonfig_File.write("fi_type="+fi_type+'\n')
						if fi_index:
							ficonfig_File.write("fi_index="+str(fi_index)+'\n')
						if fi_reg_index:				
							ficonfig_File.write("fi_reg_index="+str(fi_reg_index)+'\n')
						if fi_bit:				
							ficonfig_File.write("fi_bit="+str(fi_bit)+'\n')
						fi_cycle='' 
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

################################################################################

if __name__=="__main__":
  global inputProg, initTime,llfile
  assert len(sys.argv) > 1, 'Error. Must provide an argument to specify the IR file to inject into. (ie. python inject.py daxpy.ll'
  initTime= time.time()
  try:
    inputProg = doc["setUp"]["targetDirectoryName"]#the name of input program
  except:
    print "ERROR, Please include a targetDirectoryName field in input.yaml. See ReadMe for directions."
    exit(1)
  
  for ii,arg in enumerate(sys.argv):
    if ii==1:
      llfile = arg
    if ii>1: #add all commandline arguments to optionlist except the first two which are the this script's name, and the IR file name
      optionlist.append(arg)

  main()
