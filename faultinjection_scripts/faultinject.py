#!/usr/bin/python

import sys
import os
import getopt
import time
import random
import signal
import subprocess
import shutil

#basedir = "/home/jshwei/Desktop/splash_time_automated"
# config
basedir = "/data/experiment/LLFI/NoBrNoStack"
currdir = basedir + "/999.specrand"
progbin = currdir + "/specrand"
timeout = 100
optionlist = ["32434", "2423"]

optbin = "/data/llvm-2.9_build/Debug+Asserts/bin/opt"
llibin = "/data/llvm-2.9_build/Debug+Asserts/bin/lli"
linkbin = "/data/llvm-2.9_build/Debug+Asserts/bin/llvm-link"
instcountlib = "/data/llvm-2.9_build/Debug+Asserts/lib/LLFIProfiling.so"
filib = "/data/llvm-2.9_build/Debug+Asserts/lib/LLFI.so"
profilell = basedir + "/../lib/profiling_lib.ll"
fill = basedir + "/../lib/fi_random.ll"
outputdir = currdir + "/prog_output"
basedir = currdir + "/baseline"
errordir = currdir + "/error_output"

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
  global proflinkfile, filinkfile, mem2regfile
  mem2regfile = progbin + "-mem2reg.ll"
  proffile = progbin + "-prof.ll"
  fifile = progbin + "-fi.ll"
  proflinkfile = progbin + "-prof-link.ll"
  filinkfile = progbin + "-fi-link.ll"
  execlist = [optbin, "-load", instcountlib, '-ProfilingPass', "-profileoption=s", 
              "-S", '-o', proffile, mem2regfile]
  execCompilation(execlist)
  execlist = [optbin, "-load", filib, "-FaultInjectionRandom", '-fioption=nobranch',
              "-S", '-o', fifile, mem2regfile]
  execCompilation(execlist)
  
  execlist = [linkbin, '-S', '-o', proflinkfile, proffile, profilell]
  execCompilation(execlist)
  execlist = [linkbin, '-S', '-o', filinkfile, fifile, fill]
  execCompilation(execlist)
	
def main():
  #clear previous output
  compileProg()
  global run_number, optionlist, outputfile, proflinkfile, filinkfile
  # baseline
  outputfile = basedir + "/golden_output"
  execlist = [llibin, proflinkfile]
  execlist.extend(optionlist)
  execute(execlist)
  # fault injection
  for index in range(0, run_number):
    outputfile = outputdir + "/outputfile-" + str(index)
    errorfile = errordir + "/errorfile-" + str(index)
    execlist = [llibin, filinkfile]
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
  global run_number
  assert len(sys.argv) == 2 and "Format: prog fi_number"
  run_number = int(sys.argv[1])
  main()
