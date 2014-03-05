#! /usr/bin/env python3

import sys
import subprocess
import os
import imp

def checkRequirements():



def build():
  #Build LLVM
  os.chdir("llvm")
  p = subprocess.call(["cmake", "../llvmsrc", "-DLLVM_REQUIRES_RTTI=1", "-DCMAKE_BUILD_TYPE=Release"])
  if p != 0:
    sys.exit(p)

  p = subprocess.call("make")
  if p != 0:
    sys.exit(p)

  #Configure and Build LLFI
  llvm_paths_cmake = os.path.join(script_path, "llfisrc/config/llvm_paths.cmake")
  llvm_paths_py = os.path.join(script_path, "llfisrc/config/llvm_paths.py")
  
  cmake_File = open(llvm_paths_cmake, "w")
  LLVM_DST_ROOT = os.path.realpath("llvm")
  LLVM_SRC_ROOT = os.path.realpath("llvmsrc")
  LLVM_GXX_BIN_DIR = os.path.realpath("llvm/tools/clang")

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

def main(args):
  checkRequirements()
  if(len(args) == 1):
    build()

	
if __name__=="__main__":
  main(sys.argv)