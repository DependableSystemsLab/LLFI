#! /usr/bin/env python3

"""

%(prog)s takes project source files as input and generates a single Makefile

Usage: %(prog)s [OPTIONS] <source files>

List of options:

-o <output file>:       Intermediate representation (IR) output file
--readable:             Generate human-readable output file
--verbose:              Show verbose information
--debug:		Enable debugging symbols
--all:			Compile all source code files in the directory
--dir:			Specify a working directory
--flags:		Specify additional compiler flags
--help(-h):             Show help information
"""

import sys, os, subprocess, tempfile
script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths
import re
import glob
import copy

prog = os.path.basename(sys.argv[0])

llvmlink = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llvm-link")
clang = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "clang")
clangxx = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "clang++")

fname = 'Makefile'
newline = '\n\n'
indent = '\n\t'
filetypes = [".c", ".C", ".cpp", ".cxx", ".cp", ".CPP", ".cc"]

options = {
  "o": "a.out",
  "sources": [],
  "readable": False,
  "debug": False,
  "verbose": False,
  "all": False,
  "dir": "",
  "flags": [],
}

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = "ERROR: " + msg
    print(msg, file=sys.stderr)
  print(__doc__ % globals(), file=sys.stderr)
  sys.exit(retval)


def verbosePrint(msg, verbose):
  if verbose:
    print(msg)


def parseArgs(args):
  global options
  argid = 0
  while argid < len(args):
    arg = args[argid]
    if arg.startswith("-"):
      if arg == "-o":
        argid += 1
        options["o"] = args[argid]
      elif arg == "--readable":
        options["readable"] = True
      elif arg == "--verbose":
        options["verbose"] = True
      elif arg == "--debug":
        options["debug"] = True
      elif arg == "--all":
        options["all"] = True
      elif arg == "--dir":
        argid += 1
        options["dir"] = args[argid]
      elif arg == "--flags":
        argid += 1
        while argid < len(args) and not (args[argid].startswith('-')):
          options["flags"].append(args[argid])
          argid += 1
        argid -= 1
      elif arg == "--help" or arg == "-h":
        usage()
      else:
        usage("Invalid argument: " + arg)
    else:
        options["sources"].append(arg)
    argid += 1

  if len(options["sources"]) == 0 and options["all"] == False:
    usage("No input file(s) specified.")


def selectCompiler(sourceFiles):
  for inputfile in sourceFiles:
    if inputfile.endswith(".cpp"):
      return clangxx
  return clang


#Build the header for the Makefile
def initializeMakefile(sourceFiles):
  with open(fname, 'w') as fout:
    fout.write('CC=' + selectCompiler(sourceFiles) + '\n')
    fout.write('LINKER=' + llvmlink + '\n')
    fout.write('OUTPUT=' + options["o"] + '\n')
    
    cflags = ['-w', '-emit-llvm', '-fno-use-cxa-atexit'] #Default compiler flags
    lflags = ['-o', '$(OUTPUT)']  #Default linker flags

    if options['readable']:
      cflags.append('-S')
      lflags.append('-S')
    else:
      cflags.append('-c')

    if options['debug']:
      cflags.append('-g')

    if options['flags']:
      additionalFlags = ['-' + flag for flag in options['flags']]
      cflags += additionalFlags

    fout.write('CFLAGS=' + " ".join(cflags) + '\n') 
    fout.write('LINKER_FLAGS=' + " ".join(lflags) + '\n')


#Define the body of the Makefile
def constructMakeFile(sourceFiles):
  objList = []

  if options['readable']:
    fileextension = '.ll'
  else:
    fileextension = '.bc'

  with open(fname, 'a') as fout:
    fout.write('SRCDIR_OBJS=')

    fileexts = ['\\' + filetype + '$' for filetype in filetypes]
    regex = '|'.join(fileexts)
    
    for codeFile in sourceFiles:
      objFile = re.sub(regex, fileextension, codeFile)
      objList.append(objFile)
      fout.write(objFile + ' ')

    fout.write(newline)
    fout.write('build:')

    fout.write('$(SRCDIR_OBJS)')
  
    fout.write(indent)
    fout.write('$(LINKER) ')
    fout.write('$(LINKER_FLAGS) ')
    fout.write('$(SRCDIR_OBJS)' + newline)

    for codeFile in sourceFiles:
      objFile = re.sub(regex, fileextension, codeFile)
      fout.write(objFile + ': ' + codeFile)
      fout.write(indent)
      fout.write('$(CC) $(CFLAGS) ' + codeFile)
      fout.write(newline)
    
    fout.write('clean:')
    fout.write(indent)
    fout.write('rm -rf *.ll *.bc llfi* ')
    fout.write(options["o"])
    fout.write(newline)


def main(args):
  parseArgs(args)

  if (options["dir"]):
    os.chdir(options["dir"]) #Change working directory if dir is specified

  if (options["all"]): #Read all C/C++ files in the project directory
    fileexts = ['*' + filetype for filetype in filetypes]
    sourceFiles = []
    for files in fileexts:
      sourceFiles.extend(glob.glob(files))
  else:
    sourceFiles = options["sources"]

  initializeMakefile(sourceFiles)
  constructMakeFile(sourceFiles)

if __name__=="__main__":
  main(sys.argv[1:])

