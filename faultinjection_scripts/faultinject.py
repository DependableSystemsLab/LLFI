#!/usr/bin/python

#currently, the c file needs to be in the same directory as the script


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


def execCompilation( execlist):
  print ' '.join(execlist)
  p = subprocess.Popen(execlist)
  p.wait()

def compileProg():
	global proffile, fifile, mem2regfile, inputProg,progbin
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
	#below 2 commands are specifically for branch
	execlist = [optbin, '-load', llfilib, '-profilingpass','-S','-insttype','-includeinst=icmp', '-o', proffile, mem2reg2file]
	execCompilation(execlist)
	execlist = [optbin, '-load', llfilib, "-faultinjectionpass",'-S','-insttype','-includeinst=icmp', '-o', fifile, mem2reg2file]
	execCompilation(execlist)


	execlist = [llcbin, '-filetype=obj', '-o', proffile + '.o', proffile]
	execCompilation(execlist)
	execlist = [llcbin, '-filetype=obj', '-o', fifile + '.o', fifile]
	execCompilation(execlist)


	execlist = [llvmgcc, '-o', proffile + '.exe', proffile + '.o', '-L'+llfilinklib , '-lllfi']
	execCompilation(execlist)
	execlist = [llvmgcc, '-o', fifile + '.exe', fifile + '.o', '-L'+llfilinklib , '-lllfi']
	execCompilation(execlist)

def main():
	config()
  #clear previous output
	compileProg()
	#TEMP
	#exit(1)
	global run_number, optionlist, outputfile, proffile, fifile
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
