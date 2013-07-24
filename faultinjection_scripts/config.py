#!/usr/bin/python

import sys
import os
import re
import getopt
import distutils.core
import signal
import subprocess
import shutil
import platform

###########################################################################

def compileLLFIlib():

	buildFlag = ''
	target = ''
	osName= platform.system()

	if osName == "Linux":
		buildFlag="-shared"
		target = "libllfi.so"
	elif osName == "Darwin":
		buildFlags="-dynamiclib"
		target = "libllfi.dylib"

	currDir = os.getcwd()
	os.chdir('../lib')
	#TODO hardcoding just to make this work.. a more robust Makefile would make this a lot better
	# the Makefile currently doesnt add -fPIC to the end of the first 5 cc/g++, which causes errors for me at least
	print "cc -c -o faultinjection_lib.o faultinjection_lib.c -fPIC"
	os.system("cc -c -o faultinjection_lib.o faultinjection_lib.c -fPIC") 

	print "cc -c -o profiling_lib.o profiling_lib.c -fPIC"
	os.system("cc -c -o profiling_lib.o profiling_lib.c -fPIC") 

	print "cc -c -o utils.o utils.c -fPIC"
	os.system("cc -c -o utils.o utils.c -fPIC") 

	print "g++ -c -o commonfaultinjectors.o commonfaultinjectors.cpp -fPIC"
	os.system("g++ -c -o commonfaultinjectors.o commonfaultinjectors.cpp -fPIC") 

	print "g++ -c -o faultinjectormanager.o faultinjectormanager.cpp -fPIC"
	os.system("g++ -c -o faultinjectormanager.o faultinjectormanager.cpp -fPIC") 

	print "g++ -fPIC "+buildFlag+ " -o " +target +" faultinjection_lib.o profiling_lib.o utils.o commonfaultinjectors.o faultinjectormanager.o"
	os.system("g++ -fPIC "+buildFlag+ " -o " +target +" faultinjection_lib.o profiling_lib.o utils.o commonfaultinjectors.o faultinjectormanager.o") 
###########################################################################

def main():
	#compileLLFIlib()
	os.chdir('../src')
	llfiSrc = os.getcwd()
	llvmSrc = "/data/cho/LLFI/1/" #TODO just hardcoding for now, easier to debug, wont break my own llvm lol...eventually want  /data/llvm-2.9/lib/Transforms
	distutils.dir_util.copy_tree(llfiSrc,llvmSrc)
	os.chdir(llvmSrc+"/LLFI")
	os.system("make") 
	
if __name__=="__main__":
 
  main()
