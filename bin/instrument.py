#!/usr/bin/python

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

import sys, os, shutil
import yaml
import subprocess

script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths


optbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/opt")
llcbin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/llc")
llvmgcc = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "llvm-gcc")
llvmgxx = os.path.join(llvm_paths.LLVM_GXX_BIN_DIR, "llvm-g++")
llfilinklib = os.path.join(script_path, "../runtime_lib")
prog = os.path.basename(sys.argv[0])
basedir = os.getcwd()

if sys.platform == "linux" or sys.platform == "linux2":
  llfilib = os.path.join(script_path, "../llvm_passes/llfi-passes.so")
elif sys.platform == "darwin":
  llfilib = os.path.join(script_path, "../llvm_passes/llfi-passes.dylib")
else:
  print "ERROR: LLFI does not support platform " + sys.platform + "."
  exit(1)


options = {
  "dir": "llfi",
  "source": "",
  "L": [],
  "l": [],
  "readable": False,
  "verbose": False,
  "IRonly": False,
  "genDotGraph": False,
}


def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = "ERROR: " + msg
    print >> sys.stderr, msg
  print >> sys.stderr, __doc__ % globals()
  sys.exit(retval)


def verbosePrint(msg, verbose):
  if verbose:
    print msg


def parseArgs(args):
  global options
  argid = 0
  while argid < len(args):
    arg = args[argid]
    if arg.startswith("-"):
      if arg == "--dir":
        if options["dir"] != "llfi":
          usage("Duplicated argument: " + arg)
        argid += 1
        options["dir"] = args[argid].rstrip('/')
      elif arg == "-L":
        argid += 1
        options["L"].append(os.path.join(basedir, args[argid]))
      elif arg.startswith("-l"):
        options["l"].append(arg[2:])
      elif arg == "--readable":
        options["readable"] = True
      elif arg == "--verbose":
        options["verbose"] = True
      elif arg == "--IRonly":
        options["IRonly"] = True
      elif arg == "--help" or arg == "-h":
        usage()
      else:
        usage("Invalid argument: " + arg)
    else:
      if options["source"] != "":
        usage("More than one source files are specified")
      options["source"] = os.path.join(basedir, arg)
    argid += 1

  if options["source"] == "":
    usage("No input IR file specified")

  if '/' in options["dir"]:
    usage("Cannot specify embedded directories for --dir")
  else:
    srcpath = os.path.dirname(options["source"])
    fullpath = os.path.join(srcpath, options["dir"])
    if os.path.exists(fullpath):
      usage(options["dir"] + " already exists under " + srcpath + \
            ", you can either specify a different directory for --dir or " +\
            "remove " + options["dir"] + " from " + srcpath)
    else:
      try:
        os.mkdir(fullpath)
        options["dir"] = fullpath
      except:
        usage("Unable to create a directory named " + options["dir"] +\
              " under " + srcpath)
    

def checkInputYaml():
  #Check for input.yaml's presence
  global cOpt
  srcpath = os.path.dirname(options["source"])
  try:
    f = open(os.path.join(srcpath, 'input.yaml'), 'r')
  except:
    print "ERROR: No input.yaml file in the %s directory." % srcpath
    os.rmdir(options["dir"])
    exit(1)
  
  #Check for input.yaml's correct formmating
  try:
    doc = yaml.load(f)
    f.close()
  except:
    print "Error: input.yaml is not formatted in proper YAML (reminder: use spaces, not tabs)"
    os.rmdir(options["dir"])
    exit(1)
  
  #Check for compileOption in input.yaml
  try:
    cOpt = doc["compileOption"]
  except:
    os.rmdir(options["dir"])
    print "ERROR: Please include compileOptions in input.yaml."
    exit(1)


    
################################################################################
def execCompilation(execlist):
  verbosePrint(' '.join(execlist), options["verbose"])
  p = subprocess.Popen(execlist)
  p.wait()
  return p.returncode

################################################################################
def readCompileOption():
  global compileOptions
  
  ###Instruction selection method
  if "instSelMethod" not in cOpt:  
    print ("\n\nERROR: Please include an 'instSelMethod' key value pair under compileOption in input.yaml.\n")
    exit(1)
  else:
    #Select by instruction type
    if cOpt["instSelMethod"] == 'insttype':
      compileOptions = ['-insttype']
      if "include" not in cOpt:  
        print ("\n\nERROR: An 'Include' list must be present for the insttype method in input.yaml.\n")
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
        print ("\n\nERROR: A 'customInstSelector' key value pair must be present for the customeinstselector method in input.yaml.\n")
        exit(1)
      else:
        compileOptions.append('-fiinstselectorname='+cOpt["customInstSelector"])
        if "customInstSelectorOption" in cOpt:
          for opt in cOpt["customInstSelectorOption"]:
            compileOptions.append(opt)
    else:
      print ("\n\nERROR: Unknown Instruction selection method in input.yaml.\n")
      exit(1)

  ###Register selection method
  if "regSelMethod" not in cOpt:  
    print ("\n\nERROR: Please include an 'regSelMethod' key value pair under compileOption in input.yaml.\n")
    exit(1)
  else:
    #Select by register location
    if cOpt["regSelMethod"] == 'regloc':
      compileOptions.append('-regloc')
      if "regloc" not in cOpt:
        print ("\n\nERROR: An 'regloc' key value pair must be present for the regloc method in input.yaml.\n")
        exit(1)
      else:
        compileOptions.append('-'+cOpt["regloc"])

    #Select by custom register
    elif cOpt["regSelMethod"]  == 'customregselector':
      compileOptions.append('-customregselector')
      if "customRegSelector" not in cOpt:  
        print ("\n\nERROR: An 'customRegSelector' key value pair must be present for the customregselector method in input.yaml.\n")
        exit(1)
      else:
          compileOptions.append('-firegselectorname='+cOpt["customRegSelector"])
          if "customRegSelectorOption" in cOpt:
            for opt in cOpt["customRegSelectorOption"]:
              compileOptions.append(opt)

    else:
      print ("\n\nERROR: Unknown Register selection method in input.yaml.\n")
      exit(1)

  ###Injection Trace selection 
  if "includeInjectionTrace" in cOpt:
    for trace in cOpt["includeInjectionTrace"]:
      if trace == 'forward':
        compileOptions.append('-includeforwardtrace')
      elif trace == 'backward':
        compileOptions.append('-includebackwardtrace')
      else:
        print ("\n\nERROR: Invalid value for trace (forward/backward allowed) in input.yaml.\n")
        exit(1)

  ###Tracing Proppass
  if "tracingPropagation" in cOpt:
    print ("\nWARNING: You enabled 'tracingPropagation' option in input.yaml. "
           "The generate executables will be able to output dynamic values for instructions. "
           "However, the executables take longer time to execute. If you don't want the trace, "
           "please disable the option and re-run %s." %prog)
    compileOptions.append('-insttracepass')
    if 'tracingPropagationOption' in cOpt:
      if "debugTrace" in cOpt["tracingPropagationOption"]:
        if(str(cOpt["tracingPropagationOption"]["debugTrace"]).lower() == "true"):
          compileOptions.append('-debugtrace')
      if "maxTrace" in cOpt["tracingPropagationOption"]:
        assert isinstance(cOpt["tracingPropagationOption"]["maxTrace"], int)==True, "maxTrace must be an integer in input.yaml"
        assert int(cOpt["tracingPropagationOption"]["maxTrace"])>0, "maxTrace must be greater than 0 in input.yaml"
        compileOptions.append('-maxtrace')
        compileOptions.append(str(cOpt["tracingPropagationOption"]["maxTrace"]))

      ###Dot Graph Generation selection
      if "generateCDFG" in cOpt["tracingPropagationOption"]:
        options["genDotGraph"] = True
  

################################################################################
def _suffixOfIR():
  if options["readable"]:
    return ".ll"
  else:
    return ".bc"

def compileProg():
  global proffile, fifile, compileOptions
  srcbase = os.path.basename(options["source"])
  progbin = os.path.join(options["dir"], srcbase[0 : srcbase.rfind(".")])

  llfi_indexed_file = progbin + "-llfi_index"
  proffile = progbin + "-profiling"
  fifile = progbin + "-faultinjection"
  tmpfiles = []

  execlist = [optbin, '-load', llfilib, '-genllfiindexpass','-o', 
              llfi_indexed_file + _suffixOfIR(), options['source']]
  if options["readable"]:
    execlist.append('-S')
  if options["genDotGraph"]:
    execlist.append('-dotgraphpass')
  retcode = execCompilation(execlist)
  
  if retcode == 0:
    execlist = [optbin, '-load', llfilib, '-profilingpass']
    execlist2 = ['-o', proffile + _suffixOfIR(), llfi_indexed_file + _suffixOfIR()]
    execlist.extend(compileOptions)
    execlist.extend(execlist2)
    if options["readable"]:
      execlist.append("-S")
    retcode = execCompilation(execlist)

  if retcode == 0:
    execlist = [optbin, '-load', llfilib, "-faultinjectionpass"]
    execlist2 = ['-o', fifile + _suffixOfIR(), llfi_indexed_file + _suffixOfIR()]
    execlist.extend(compileOptions)
    execlist.extend(execlist2)
    if options["readable"]:
      execlist.append("-S")
    retcode = execCompilation(execlist)

  if retcode != 0:
    print >> sys.stderr, "\nERROR: there was an error during running the "\
                         "instrumentation pass, please follow"\
                         " the provided instructions for %s." % prog
    shutil.rmtree(options['dir'], ignore_errors = True)
    sys.exit(retcode)

  if not options["IRonly"]:
    if retcode == 0:
      execlist = [llcbin, '-filetype=obj', '-o', proffile + '.o', proffile + _suffixOfIR()]
      tmpfiles.append(proffile + '.o')
      retcode = execCompilation(execlist)
    if retcode == 0:
      execlist = [llcbin, '-filetype=obj', '-o', fifile + '.o', fifile + _suffixOfIR()]
      tmpfiles.append(fifile + '.o')
      retcode = execCompilation(execlist)

    liblist = []
    for lib_dir in options["L"]:
      liblist.extend(["-L", lib_dir])
    for lib in options["l"]:
      liblist.append("-l" + lib)
    liblist.append("-Wl,-rpath")
    liblist.append(llfilinklib)

    if retcode == 0:
      execlist = [llvmgcc, '-o', proffile + '.exe', proffile + '.o', '-L'+llfilinklib , '-lllfi-rt']
      execlist.extend(liblist)
      retcode = execCompilation(execlist)
      if retcode != 0:
        print "...Error compiling with " + os.path.basename(llvmgcc) + ", trying with " + os.path.basename(llvmgxx) + "." 
        execlist[0] = llvmgxx
        retcode = execCompilation(execlist)
    if retcode == 0:
      execlist = [llvmgcc, '-o', fifile + '.exe', fifile + '.o', '-L'+llfilinklib , '-lllfi-rt']
      execlist.extend(liblist)
      retcode = execCompilation(execlist)
      if retcode != 0:
        print "...Error compiling with " + os.path.basename(llvmgcc) + ", trying " + os.path.basename(llvmgxx) + "." 
        execlist[0] = llvmgxx
        retcode = execCompilation(execlist)


    for tmpfile in tmpfiles:
      try:
        os.remove(tmpfile)
      except:
        pass
    if retcode != 0:
      print >> sys.stderr, "\nERROR: there was an error during linking and generating executables,"\
                           "Please take %s and %s and generate the executables manually (linking llfi-rt "\
                           "in directory %s)." %(proffile + _suffixOfIR(), fifile + _suffixOfIR(), llfilinklib)
      sys.exit(retcode)
    else:
      print >> sys.stderr, "\nSuccess"


################################################################################
def main(args):
  parseArgs(args)
  checkInputYaml()
  readCompileOption()
  compileProg()

################################################################################

if __name__=="__main__":
  main(sys.argv[1:])
