#!/usr/bin/env python3


"""

%(prog)s takes source files(s) as input and generate a single IR file

Usage: %(prog)s [OPTIONS] <source files>

List of options:

-o <output file>:       Intermediate representation (IR) output file
-I <include directory>: Include directory for header files
--readable:             Generate human-readable output file
--verbose:              Show verbose information
--debug:		Enable debugging symbols
--help(-h):             Show help information
"""

import sys, os, subprocess, tempfile
script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths

llvmlink = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llvm-link")
llvmgcc = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "clang")
llvmgxx = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "clang++")
prog = os.path.basename(sys.argv[0])

basedir = os.getcwd()

options = {
  "o": "a.out",
  "sources": [],
  "I": [],
  "readable": False,
  "debug": False,
  "verbose": False,
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
        options["o"] = os.path.join(basedir, args[argid])
      elif arg == "-I":
        argid += 1
        options["I"].append(os.path.join(basedir, args[argid]))
      elif arg == "--readable":
        options["readable"] = True
      elif arg == "--verbose":
        options["verbose"] = True
      elif arg == "--debug":
        options["debug"] = True
      elif arg == "--help" or arg == "-h":
        usage()
      else:
        usage("Invalid argument: " + arg)
    else:
      options["sources"].append(os.path.join(basedir, arg))
    argid += 1

  if len(options["sources"]) == 0:
    usage("No input file(s) specified.")


################################################################################
def execute(execlist):
  verbosePrint(' '.join(execlist), options["verbose"])
  p = subprocess.Popen(execlist)
  p.wait()
  return p.returncode


def compileToIR(outputfile, inputfile):
  if inputfile.endswith(".c"):
    execlist = [llvmgcc]
  else:
    execlist = [llvmgxx]

  execlist.extend(['-w', '-emit-llvm', '-o', outputfile, inputfile])

  for header_dir in options["I"]:
    execlist.extend(['-I', header_dir])

  if options['readable']:
    execlist.append('-S')
  else:
    execlist.append('-c')

  if options['debug']:
    execlist.append('-g')

  return execute(execlist)


def linkFiles(outputfile, inputlist):
  execlist = [llvmlink, '-o', outputfile]

  if options['readable']:
    execlist.append('-S')

  execlist.extend(inputlist)
  return execute(execlist)

################################################################################
def compileProg():
  outputfile = options["o"]
  srcfiles = options["sources"]
  verbosePrint("Source files to be compiled: ", options["verbose"])
  verbosePrint(", ".join(srcfiles), options["verbose"])
  verbosePrint("\n======Compile======", options["verbose"])

  if len(srcfiles) == 1:
    retcode = compileToIR(outputfile, srcfiles[0])
  else:
    tmpfiles = []
    for src in srcfiles:
      file_handler, tmpfile = tempfile.mkstemp()
      tmpfiles.append(tmpfile)
      retcode = compileToIR(tmpfile, src)
      if retcode != 0:
        break

    if retcode == 0:
      retcode = linkFiles(outputfile, tmpfiles)

  # cleaning up the temporary files
    for tmpfile in tmpfiles:
      try:
        os.remove(tmpfile)
      except:
        pass

  if retcode != 0:
    print("\nERROR: there was a compilation error, please follow"\
                          " the provided instructions for %s or compile the "\
                          "source file(s) to one single IR file manually." % prog, file=sys.stderr)
    sys.exit(retcode)


################################################################################
def main(args):
  parseArgs(args)
  compileProg()


if __name__=="__main__":
  main(sys.argv[1:])
