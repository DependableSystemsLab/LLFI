#! /usr/bin/env python3

"""

%(prog)s takes a single IR file as input and generates IR files (and executables, depending on the -IRonly option) with instrumented profiling and fault injection function calls

Usage: %(prog)s [OPTIONS] <source IR file>

List of options:

--dir <relative directory>: Generate the instrumented IRs and executables to '<directory of source IR file>/<relative directory>', default: llfi
-L <library directory>:     Add <library directory> to the search directories for -l
-l<library>:                link <library>
--readable:                 Generate human-readable IR files
--IRonly:                   Only generate the instrumented IR files, and you will do the linking and create the executables manually
--verbose:                  Show verbose information
--help(-h):                 Show help information

Prerequisite:
You need to have 'input.yaml' under the same directory as <source IR file>, which contains appropriate options for LLFI
"""

# Everytime the contents of compileOption is changed in input.yaml
# this script should be run to create new fi.exe and prof.exe


import sys, os
import shutil, errno
import yaml
import subprocess

script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths

prog = os.path.basename(sys.argv[1])
#infile=sys.argv[2]
basename= os.path.splitext(prog)[0]
basedir= os.getcwd()
#print (basedir)

instrumentPath = os.path.join(llvm_paths.LLVM_DST_ROOT, "../llfi/bin/instrument")
srcpath = os.path.dirname(os.path.join(basedir, sys.argv[1]))
srcfile = os.path.join(basedir, sys.argv[1])
srcyaml = os.path.join(srcpath, "input.yaml")
srcsample = os.path.join(srcpath, "sample.txt")
MFMP = os.path.join(srcpath, "Multiple-Failure-Modes")
#print(os.path.dirname(sys.argv[1]))
if os.path.exists(MFMP):
	shutil.rmtree(MFMP)
srcdirect = os.path.dirname(sys.argv[1])
newyamldir = os.path.join(srcdirect, "Multiple-Failure-Modes")
#if not os.path.exists(MFMP):
#  os.makedirs(newyamldir)
os.makedirs(newyamldir)

shutil.copy(srcfile, MFMP)
shutil.copy(srcyaml, MFMP)
#shutil.copy(srcsample, MFMP)
os.chdir(MFMP)
########################################################################################################
def SplitMasterInputYaml():

  global i , size, master

  try:
    fo = open(os.path.join(srcpath, 'input.yaml'), 'r')
    #fo = open("input.yaml", "r") 
  except:
    fo= open("Multiple-Failure-Modes/input.yaml", "r")
    os.chdir("Multiple-Failure-Modes/") 
  master=list(fo)
  m=master.index('          include:\n')
  n=master.index('    regSelMethod: customregselector\n')
  MFM=master[m+1:n]
  size= len(MFM)
  del master[m+1:n]

 # split master yaml to child yaml(s) 
  for i in range (0,size):
    if MFM[i]!= '\n':
      master.insert(m+1,MFM[i])
    
 # write to a file
      if (os.path.exists('input%s.yaml' %(i))):
        os.remove('input%s.yaml' %(i))
      with open('input%s.yaml' %(i), mode='wt', encoding='utf-8') as myfile:
        for lines in master:
          print(lines, file = myfile)
      myfile.close
      del master[m+1] 
    else : size=size-1
  fo.close()
  for x in range (0,size):
    cloneProject("../Multiple-Failure-Modes/", "../MFM%s" %x)
 

  #rename child yaml(s) to input.yaml
  for j in range (0, size):
    os.rename ('../MFM%s/input%s.yaml' %(j, j),'../MFM%s/input.yaml' %j)
    for n in range (0, size): 
      if n!=j :
        os.remove ('../MFM%s/input%s.yaml' %(j, n))
  
  callinstrument(prog)   
    
    
########################################################################################
def cloneProject(src, dst):
    try:
        if os.path.exists(dst):
            shutil.rmtree(dst)
        shutil.copytree(src, dst)
    except OSError as exc: # python >2.5
        if exc.errno == errno.ENOTDIR:
            shutil.copy(src, dst)
        else: raise
#######################################################################################################
def callinstrument(prog):
  for j in range (0, size):  
    path = "../MFM%s" %j
    os.chdir( path )
    result = subprocess.check_output([instrumentPath, '-lpthread', '--readable',prog])
    print ("instrumentation done")
#######################################################################################################

def main(prog):
  SplitMasterInputYaml()
  #callinstrument(prog)
  
################################################################################

if __name__ == '__main__':
	main(sys.argv[1])
