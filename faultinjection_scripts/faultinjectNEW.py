#!/usr/bin/python

#currently, the c file(s) needs to be in the same directory as the script
#basedir is actually the directory with the script and c file(s)
#curdir is where the compilation and execution files will be stored

#To run this, please change optbin,llcbin,llvmgcc,llfilib,llfilinklib, and basedir to match your system
# sys.path.append() a path that points to your local yaml library

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
llfilib = "/data/llvm-2.9/Release/lib/LLFI.so"
llfilinklib = "/data/LLFI-experimental-master/lib"
optionlist = []
timeout = 500
compileOverride = False
runOverride = False
compileOnly = False
#Check for input.yaml's presence
try:
	f = open('input.yaml','r')
except:
	print "ERROR. No input.yaml file in the current directory."
	exit(1)

#Just a little tweak to make the output look less clustered
print "\n"	

#Check for input.yaml's correct formmating
try:
	doc = yaml.load(f)
	f.close()
	if "kernelOption" in doc:
		for opt in doc["kernelOption"]:	
			if opt=="forceRun":
				runOverride = True
				print "Kernel: Forcing run"
			if opt=="forceCompile":
				compileOverride = True
				print "Kernel: Forcing compile\n"
			if opt=="compileOnly":
				compileOnly = True
except:
	print "Error. input.yaml is not formatted in proper YAML (reminder: use spaces, not tabs)"
	exit(1)

try:
	cOpt = doc["compileOption"]
except:
	print "ERROR in input.yaml. Please include compileOptions."
	exit(1)

#config is now executed after main
################################################################################
def config():
	global inputProg,progbin,inputdir,outputdir,basedir,errordir
	#basedir = "/home/jshwei/Desktop/splash_time_automated"
	# config
	basedir = os.path.dirname(os.path.abspath(__file__)) #path of directory where script is running on
	currdir = basedir + "/"+inputProg
	progbin = currdir + "/"+inputProg
	

	#linkbin = "/data/llvm-2.9/Debug+Asserts/bin/llvm-link"
	#llibin = "/data/llvm-2.9/Debug+Asserts/bin/lli"
	#profilell = basedir + "/../lib/profiling_lib.ll"
	#fill = basedir + "/../lib/fi_random.ll"
	
	inputdir = currdir + "/prog_input"
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
	if not os.path.isdir(inputdir):
		os.mkdir(inputdir)
		
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

	#write to scriptMeta.yaml, used for auto-Compiling
	#write the input.yaml's last modification time 
	metaFile = open("scriptMeta.yaml","w")
	metaFile.write("lastModified: ")
	metaFile.write(str(os.path.getmtime("input.yaml")))
	metaFile.write("\n")
	metaFile.write(yaml.dump(cOpt))
	metaFile.close()

################################################################################

def compileProg():
	global proffile, fifile, mem2regfile,progbin,compileOptions
	inputllfile = progbin + ".ll"
	mem2regfile = progbin + "-mem2reg.ll"
	mem2reg2file = progbin + "-mem2reg2.ll"
	proffile = progbin + "-prof.ll"
	fifile = progbin + "-fi.ll"

	#Loop through directory for all c, cc, cpp files
	srcFiles = [ each for each in os.listdir('.') if each.lower().endswith('.c') or each.lower().endswith('.cc') or each.lower().endswith('.cpp')] 
	
	print "======Compile======"

  #TODO -S needs to be an option
	if len(srcFiles) ==1:
		execlist = [llvmgcc,'-I.','-emit-llvm','-S', '-o', inputllfile, srcFiles[0]]
		execCompilation(execlist)
	elif len(srcFiles) >1:
		#llvmgcc for each .c file
		for  ii, src in enumerate(srcFiles):
			execlist = [llvmgcc,'-I.','-emit-llvm','-S', '-o', progbin +str(ii)+".ll", src]
			execCompilation(execlist)
		execlist = [llvmlink, '-S','-o',inputllfile]
		#building llvmlink command
		for ii, src in enumerate(srcFiles):
			execlist.append(progbin+str(ii)+".ll")
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

	print "\n"
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
	#move all newly created files that are not "llfi.stat.prof.txt" < -- since this is a product of profiling
	for each in[file for file in os.listdir(".")]:
		if each not in dirBefore and each !="llfi.stat.prof.txt":
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
def autoCompile(): #returns boolean:true if program needs to be compiled, or 
				 #recompiled due to an editted input.yaml, false otherwise
	try:
		#scriptMeta stores the modification date of the input.yaml that this script used previously 
		#to compile fi and prof.exe in this directory
		metaFile = open("scriptMeta.yaml","r")
	except:
		print "Autocompiler: Need to compile - first run.\n"
		return True
	
	if not os.path.isfile(progbin+"-prof.ll.exe"):
			#case for compile errors where no .exe files are generated yet
			print "Autocompiler: Need to compile until there is a successful compilation.\n"
			return True

	try:
		meta = yaml.load(metaFile)
		metaFile.close()
		
		if(	str(meta["lastModified"])==str(os.path.getmtime("input.yaml"))):
			print "Autocompiler: Don't need to recompile - no changes made to input.yaml.\n"
			return False
		else:
			for key in  cOpt:
				if cOpt[key]!=meta[key]:
					#compile options updated
					print "Autocompiler: Need to recompile - compile option in input.yaml has been edited.\n"
					return True
			#input.yaml updated, but not compile options
			print "Autocompiler: Don't need to recompile - no changes made to compile options in input.yaml.\n"
			return False
	except:
		#shouldn't come here unless user has manually changed scriptMeta.yaml
		print "ERROR in scriptMeta.yaml. Please delete the file and run this script again.\n"
		metaFile.close()
		exit(1)
	
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
	global optionlist, outputfile, proffile, fifile, totalcycles,inputList,run_id	
	
	config()
	
	if(compileOverride or autoCompile()): 
		readCompileOption()
		compileProg()

	if(compileOnly):
		exit(1)

	storeInputFiles()
	# baseline
	outputfile = basedir + "/golden_output"
	execlist = [ progbin + "-prof.ll" + '.exe']#TODO change back to proffile 
	execlist.extend(optionlist)
	run_id=''#execute requires run_id to be defined
	print "======Profiling======"
	execute(execlist)

	# get total num of cycles
	readCycles()

	#Set up each config file and its corresponding run_number
	try:
		rOpt = doc["runOption"]
	except:
		print "ERROR ininput.yaml. Please include runOption."
		exit(1)

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
			if "fi_type" in run["run"]:
				fi_type=run["run"]["fi_type"]
				checkValues("fi_type",fi_type)
			if "fi_cycle" in run["run"]:
				fi_cycle=run["run"]["fi_cycle"]
				checkValues("fi_cycle",fi_cycle)
			if "fi_index" in run["run"]:
				fi_index=run["run"]["fi_index"]	
				checkValues("fi_index",fi_index)
			if "fi_reg_index" in run["run"]:
				fi_reg_index=run["run"]["fi_reg_index"]	
				checkValues("fi_reg_index",fi_reg_index)	
			if "fi_bit" in run["run"]:
				fi_bit=run["run"]["fi_bit"]
				checkValues("fi_bit",fi_bit,run_number,fi_cycle,fi_index,fi_reg_index)

	
			# fault injection
			for index in range(0, run_number):
				run_id = str(ii)+"-"+str(index)
				outputfile = outputdir + "/outputfile-" + "run-"+run_id
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
  global inputProg

  try:
    inputProg = doc["setUp"]["targetDirectoryName"]#the name of input program
  except:
    print "ERROR, Please include a targetDirectoryName field in input.yaml. See ReadMe for directions."
    exit(1)

  for ii,arg in enumerate(sys.argv):
    if ii: #add all commandline arguments to optionlist except the first one which is the this script's name
      optionlist.append(arg)

  main()
