#! /usr/bin/env python3

"""

%(prog)s starts LLFI GUI application.

Usage: %(prog)s [OPTIONS] <source IR file>

List of options:

--help(-h):                 Show help information

"""

import os
import sys
import subprocess

prog = os.path.basename(sys.argv[0])
script_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append((os.path.join(script_path, '../config')))
import java_paths

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = "ERROR: " + msg
    print(msg, file=sys.stderr)
  print(__doc__ % globals(), file=sys.stderr)
  sys.exit(retval)

def parseArgs(args):
  global options
  argid = 0
  while argid < len(args):
    arg = args[argid]
    if arg.startswith("-"):
      if arg == "--help" or arg == "-h":
        usage()

def startGUI():
	lib_path = os.path.join(script_path, os.pardir, 'gui/application/lib/*')
	class_path = os.path.join(script_path, os.pardir, 'gui')
	execlist = [java_paths.JAVA_EXECUTABLE, '-classpath', 
				java_paths.CMAKE_JAVA_INCLUDE_PATH+':'+lib_path+':'+class_path, 
				'application.Main']
	print(' '.join(execlist))
	p = subprocess.Popen(execlist)
	return

################################################################################
def main(args):
  parseArgs(args)
  startGUI()

################################################################################

if __name__=="__main__":
  main(sys.argv[1:])
    
