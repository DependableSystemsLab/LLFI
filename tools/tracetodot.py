#! /usr/bin/env python3

#  tracetodot.py
#  Author: Yilun Song
#  This python script is part of the LLFI tracing system
#  This script generates all intermediate and final trace files needed to view trace propogation flows.
#  Requires: Please run this scripts in the folder that contains the llfi trace files e.g. the llfi_stat_output folder by default
#  Output: Generate trace different report files and its .dot files to the folder trace_report_output



"""

%(prog)s needs to be called in the folder that contains the llfi trace files (e.g. /llfi_stat_output)

The trace different report files and .dot files will be generated to the folder trace_report_output in parallel with the folder llfi_stat_output

Usage: %(prog)s [OPTIONS]

List of options:

--help(-h):             Show help information

"""


import sys, os
import subprocess
import shlex

prog = os.path.basename(sys.argv[0])



def parseArgs(args):
  argid = 0
  while argid < len(args):
    arg = args[argid]
    if arg.startswith("-"):
      if arg == "--help" or arg == "-h":
        usage()
      else:
        usage("Invalid argument: " + arg)
    argid += 1


def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = 1
    msg = "ERROR: " + msg
    print(msg, file=sys.stderr)
  print(__doc__ % globals(), file=sys.stderr)
  sys.exit(retval)


def findPath():
	global currentpath, scriptdir

	currentpath = os.getcwd()
	#print (currentpath)

	scriptdir = os.path.dirname(os.path.abspath(__file__))



def makeTraceOutputFolder():
	global traceOutputFolder, goldenTraceFilePath
	traceOutputFolder = os.path.abspath(os.path.join(currentpath, "../trace_report_output"))
	#print (traceOutputFolder)
	goldenTraceFilePath = os.path.abspath(os.path.join(currentpath, "../baseline/llfi.stat.trace.prof.txt"))
	if not os.path.exists(traceOutputFolder):
		os.makedirs(traceOutputFolder)
	else:
		# Remove the contents in traceOutputFolder
		for f in os.listdir(traceOutputFolder):
			file_path = os.path.join(traceOutputFolder,f)
			if os.path.isfile(file_path):
				os.unlink(file_path)
	if not os.path.isfile(goldenTraceFilePath):
		print ("Cannot find golden Trace File 'llfi.stat.trace.prof.txt'")



def executeTraceDiff():
	traceFileCount = 0
	log_path =os.path.abspath(os.path.join(traceOutputFolder, "stderr_log.txt"))
	log_file =open(log_path ,'w')
	#Parse the goldenTraceFile path
	tempgoldenTraceFilePath = goldenTraceFilePath
	while "(" in tempgoldenTraceFilePath and not "\(" in tempgoldenTraceFilePath:
		tempgoldenTraceFilePath = tempgoldenTraceFilePath[:tempgoldenTraceFilePath.find("(")]+'\('+ tempgoldenTraceFilePath[tempgoldenTraceFilePath.find("(")+1:]
	while ")" in tempgoldenTraceFilePath and not "\)" in tempgoldenTraceFilePath:
		tempgoldenTraceFilePath = tempgoldenTraceFilePath[:tempgoldenTraceFilePath.find(")")]+'\)'+ tempgoldenTraceFilePath[tempgoldenTraceFilePath.find(")")+1:]
	tempScriptdir = scriptdir
	#Parse the scriptdir path
	while "(" in tempScriptdir and not "\(" in tempScriptdir:
		tempScriptdir = tempScriptdir[:tempScriptdir.find("(")]+'\('+ tempScriptdir[tempScriptdir.find("(")+1:]
	while ")" in tempScriptdir and not "\)" in tempScriptdir:
		tempScriptdir = tempScriptdir[:tempScriptdir.find(")")]+'\)'+ tempScriptdir[tempScriptdir.find(")")+1:]
	temptraceOutputFolder = traceOutputFolder
	#Parse the traceOutputFolder path
	while "(" in temptraceOutputFolder and not "\(" in temptraceOutputFolder:
		temptraceOutputFolder = temptraceOutputFolder[:temptraceOutputFolder.find("(")]+'\('+ temptraceOutputFolder[temptraceOutputFolder.find("(")+1:]
	while ")" in temptraceOutputFolder and not "\)" in temptraceOutputFolder:
		temptraceOutputFolder = temptraceOutputFolder[:temptraceOutputFolder.find(")")]+'\)'+ temptraceOutputFolder[temptraceOutputFolder.find(")")+1:]
	for file in os.listdir(currentpath):
		if file.endswith(".txt") and file.startswith("llfi.stat.trace."):
			cmd = tempScriptdir+"/tracediff "+tempgoldenTraceFilePath+" "+file+" > "+temptraceOutputFolder+"/TraceDiffReportFile"+file[file.find("llfi.stat.trace")+len("llfi.stat.trace"):]
			p =subprocess.call(cmd,shell=True,stderr=log_file)
			traceFileCount += 1
	#Check if trace files present, if not show error messages
	if not traceFileCount > 0:
		print ("Cannot find Trace input files.")
		print ("Please make sure you are running this script in the llfi_stat_output folder")

def generateDotFile():
	log_path =os.path.abspath(os.path.join(traceOutputFolder, "stderr_log.txt"))
	log_file =open(log_path ,'a')
	goldenTraceDotFile = os.path.abspath(os.path.join(currentpath, "../../../llfi.stat.graph.dot"))
	if not os.path.isfile(goldenTraceDotFile):
		goldenTraceDotFile = os.path.abspath(os.path.join(currentpath, "../../llfi.stat.graph.dot"))
		if not os.path.isfile(goldenTraceDotFile):
			print ("Cannot find golden Trace Dot File 'llfi.stat.graph.dot'")

	#Parse the goldenTraceFile path
	tempgoldenTraceFilePath = goldenTraceFilePath
	while "(" in tempgoldenTraceFilePath and not "\(" in tempgoldenTraceFilePath:
		tempgoldenTraceFilePath = tempgoldenTraceFilePath[:tempgoldenTraceFilePath.find("(")]+'\('+ tempgoldenTraceFilePath[tempgoldenTraceFilePath.find("(")+1:]
	while ")" in tempgoldenTraceFilePath and not "\)" in tempgoldenTraceFilePath:
		tempgoldenTraceFilePath = tempgoldenTraceFilePath[:tempgoldenTraceFilePath.find(")")]+'\)'+ tempgoldenTraceFilePath[tempgoldenTraceFilePath.find(")")+1:]
	tempScriptdir = scriptdir
	#Parse the scriptdir path
	while "(" in tempScriptdir and not "\(" in tempScriptdir:
		tempScriptdir = tempScriptdir[:tempScriptdir.find("(")]+'\('+ tempScriptdir[tempScriptdir.find("(")+1:]
	while ")" in tempScriptdir and not "\)" in tempScriptdir:
		tempScriptdir = tempScriptdir[:tempScriptdir.find(")")]+'\)'+ tempScriptdir[tempScriptdir.find(")")+1:]
	temptraceOutputFolder = traceOutputFolder
	#Parse the traceOutputFolder path
	while "(" in temptraceOutputFolder and not "\(" in temptraceOutputFolder:
		temptraceOutputFolder = temptraceOutputFolder[:temptraceOutputFolder.find("(")]+'\('+ temptraceOutputFolder[temptraceOutputFolder.find("(")+1:]
	while ")" in temptraceOutputFolder and not "\)" in temptraceOutputFolder:
		temptraceOutputFolder = temptraceOutputFolder[:temptraceOutputFolder.find(")")]+'\)'+ temptraceOutputFolder[temptraceOutputFolder.find(")")+1:]
	tempgoldenTraceDotFile = goldenTraceDotFile
	#Parse the traceOutputFolder path
	while "(" in tempgoldenTraceDotFile and not "\(" in tempgoldenTraceDotFile:
		tempgoldenTraceDotFile = tempgoldenTraceDotFile[:tempgoldenTraceDotFile.find("(")]+'\('+ tempgoldenTraceDotFile[tempgoldenTraceDotFile.find("(")+1:]
	while ")" in tempgoldenTraceDotFile and not "\)" in tempgoldenTraceDotFile:
		tempgoldenTraceDotFile = tempgoldenTraceDotFile[:tempgoldenTraceDotFile.find(")")]+'\)'+ tempgoldenTraceDotFile[tempgoldenTraceDotFile.find(")")+1:]


	for file in os.listdir(traceOutputFolder):
		if file.startswith("TraceDiffReportFile"):
			# Parse the name
			name = file[file.find("TraceDiffReportFile")+len("TraceDiffReportFile"):]
			name = name.replace("txt", "dot")
			cmd = tempScriptdir+"/traceontograph "+temptraceOutputFolder+"/"+file+" "+tempgoldenTraceDotFile+" > "+ temptraceOutputFolder+"/TraceGraph"+name
			p =subprocess.call(cmd,shell=True,stderr=log_file)


def main(args):
	global currentpath, scriptdir, traceOutputFolder, goldenTraceFilePath
	parseArgs(args)
	findPath()
	makeTraceOutputFolder()
	executeTraceDiff()
	generateDotFile()

if __name__=="__main__":
  main(sys.argv[1:])
