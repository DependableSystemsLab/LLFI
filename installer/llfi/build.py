#! /usr/bin/env python3

import sys
import subprocess
import os
import imp
import site

def checkRequirements():
  return 0

def build(buildLLVM):
  if buildLLVM:
    #Build LLVM
    os.chdir("llvm")
    p = subprocess.call(["cmake", "../llvmsrc", "-DLLVM_REQUIRES_RTTI=1", "-DCMAKE_BUILD_TYPE=Release"])
    if p != 0:
      sys.exit(p)

    p = subprocess.call("make")
    if p != 0:
      sys.exit(p)
    os.chdir("..")


  #Configure and Build LLFI
  script_path = os.getcwd()
  llvm_paths_cmake = os.path.join(script_path, "llfisrc/config/llvm_paths.cmake")
  llvm_paths_py = os.path.join(script_path, "llfisrc/config/llvm_paths.py")
  
  cmake_File = open(llvm_paths_cmake, "w")
  LLVM_DST_ROOT = os.path.realpath("llvm")
  LLVM_SRC_ROOT = os.path.realpath("llvmsrc")
  LLVM_GXX_BIN_DIR = os.path.realpath("clang/bin")

  cmake_File.write("set(LLVM_DST_ROOT " + LLVM_DST_ROOT + ")\n")
  cmake_File.write("set(LLVM_SRC_ROOT " + LLVM_SRC_ROOT + ")\n")
  cmake_File.close()

  py_File = open(llvm_paths_py, "w")
  py_File.write("LLVM_DST_ROOT = " + '"' + LLVM_DST_ROOT + '"\n')
  py_File.write("LLVM_SRC_ROOT = " + '"' + LLVM_SRC_ROOT + '"\n')
  py_File.write("LLVM_GXX_BIN_DIR = " + '"' + LLVM_GXX_BIN_DIR + '"\n')
  py_File.close()

  os.chdir("llfi")
  p = subprocess.call(["cmake", "../llfisrc"])
  if p != 0:
    sys.exit(p)

  p = subprocess.call("make")
  if p != 0:
    sys.exit(p)

  os.chdir("..")

  pyyaml_path = os.path.join(script_path,"pyyaml")
  os.chdir("pyyamlsrc")

  p = subprocess.call(["python3","setup.py","install","--prefix="+pyyaml_path])
  if p != 0:
    sys.exit(p)

  os.chdir("..")

def addEnvs():
  scriptPath = os.path.dirname(os.path.realpath(__file__))
  llfibuildPath = os.path.join(scriptPath, "llfi/")

  majorVer = sys.version_info[0]
  minorVer = sys.version_info[1]
  pyVersion = str(majorVer) + "." + str(minorVer)
  pyPath = os.path.join(scriptPath, "pyyaml/lib/python"+pyVersion+"/site-packages/")

  homePath = os.environ['HOME']
  tcshPath = os.path.join(homePath, ".tcshrc")
  
  with open(tcshPath, "a") as rcFile:
    rcFile.write("setenv PYTHONPATH " + pyPath + "\n")
    rcFile.write("setenv llfibuild " + llfibuildPath + "\n") 

def main(args):
  buildLLVM=1
  while (len(args)>1):
    arg = args.pop()
    if(arg == "-nobuildLLVM"):
      buildLLVM=0
    else:
      print("Unknown Argument")
      quit() 
  checkRequirements()
  build(buildLLVM)

  addEnvs()

  
if __name__=="__main__":
  main(sys.argv)
