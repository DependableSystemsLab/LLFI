#! /usr/bin/env python3

"""

%(prog)s is a wrapper for LLFI instrument command to generate multiple work directories for multiple software failure modes (instruction selector) specified in single input.yaml file. The single input.yaml with multiple software failure modes will be splited into multiple input.yaml files, each with only one failure mode enabled and placed in a specific subdirectory under current path.

Usage: %(prog)s [OPTIONS] <source IR file>

List of options:

-L <library directory>:     Add <library directory> to the search directories for -l
-l<library>:                link <library>
--readable:                 Generate human-readable IR files
--IRonly:                   Only generate the instrumented IR files, and you will do the linking and create the executables manually
--verbose:                  Show verbose information
--help(-h):                 Show help information

Prerequisite:
You need to have 'input.yaml' under the same directory as <source IR file>, which contains appropriate options for LLFI. Usually, this command is only applicable for input.yaml file with a list of software failure modes included, i.e. using customInstSelector in instSelMethod and including software fault instruction selector (e.g. BufferOverflow(API)).
"""

import sys, os, shutil
import yaml
import subprocess

prog = os.path.basename(sys.argv[0])
script_path = os.path.realpath(os.path.dirname(__file__))
sys.path.append(os.path.join(script_path, '../config'))
import llvm_paths

instrument_script = os.path.join(script_path, 'instrument')
# basedir and options are assigned in parseArgs(args)
basedir = ""
options = []

def parseArgs(args):
	global basedir
	global options
	cwd = os.getcwd()
	for arg in args:
		option = arg
		if os.path.isfile(arg):
			basedir = os.path.realpath(os.path.dirname(arg))
			option = os.path.basename(arg)
		options.append(option)
	os.chdir(basedir)

def usage(msg = None):
  retval = 0
  if msg is not None:
    retval = -1
    msg = "ERROR: " + msg
    print(msg, file=sys.stderr)
  print(__doc__ % globals(), file=sys.stderr)
  sys.exit(retval)

def parseMasterYaml():
	global basedir
	master_yaml_dict = {}
	model_list = []
	try:
		with open('input.yaml', 'r') as master_yaml_file:
			master_yaml_dict = yaml.load(master_yaml_file)
	except:
		print ("ERROR: Unable to find input.yaml or load the input.yaml under basedir directory")
		print (basedir)
		sys.exit(-1)
	try:
		model_list = list(master_yaml_dict['compileOption']['instSelMethod'][0]['customInstselector']['include'])
	except:
		print ("ERROR: this wrapper script is not applicable on the input.yaml under current directory. Please note this script is only applicable on input.yaml files with multiple software failure models defined.")
		print (basedir)
		sys.exit(-1)
	return master_yaml_dict, model_list

def splitMasterYaml(master_yaml_dict, model_list):
	global basedir
	for model in model_list:
		include_list = [model]
		slave_yaml_dict = dict(master_yaml_dict)
		slave_yaml_dict['compileOption']['instSelMethod'][0]['customInstselector']['include'] = include_list
		slave_yaml_text = yaml.dump(slave_yaml_dict, default_flow_style=False)
		workdir = os.path.join(basedir, "llfi-"+model)
		try:
			with open(os.path.join(workdir, 'input.yaml'), 'w') as f:
				f.write(slave_yaml_text)
		except:
			print ("ERROR: Unable to write slave input.yaml file for model: ", model)
			print ("workdir: ", workdir)
			sys.exit(-1)
	return 0	

def maybeRequired(abs_path):
	basename = os.path.basename(abs_path)
	if basename.startswith('llfi'):
		return False
	elif basename == 'input.yaml':
		return False
	return True

def prepareDirs(model_list):
	global basedir
	stuffs_under_basedir = [f for f in os.listdir(basedir) if maybeRequired(os.path.join(basedir, f))]
	for model in model_list:
		workdir = os.path.join(basedir, "llfi-"+model)
		if os.path.exists(workdir):
			try:
				if os.path.isdir(workdir):
					shutil.rmtree(workdir)
				else:
					os.remove(workdir)
			except:
				print ("ERROR: Unable to remove:", workdir, "for model:", model)
				sys.exit(-1)
		os.makedirs(workdir)
		for s in stuffs_under_basedir:
			s_path = os.path.join(basedir, s)
			try:
				if os.path.isfile(s_path):
					shutil.copy(s_path, workdir)
				else:
					shutil.copytree(s_path, workdir)
			except:
				print ("ERROR: Unable to copy:", s_path, "\nto:", workdir)
				sys.exit(-1)
	return 0


def callInstrument(model_list):
	global basedir
	global options
	num_failed = 0
	for model in model_list:
		workdir = os.path.join(basedir, "llfi-"+model)
		os.chdir(workdir)
		command = [instrument_script]
		command.extend(options)
		try:
			o = subprocess.check_output(command, stderr=sys.stderr)
		except subprocess.CalledProcessError:
			print ("instrumenting:", model, " failed!")
			num_failed += 1
		else:
			print (o.decode())
			print ("instrumenting:", model, " succeed!")
		os.chdir(basedir)
	return num_failed

def main():
	parseArgs(sys.argv[1:])
	master_yaml_dict, model_list = parseMasterYaml()
	prepareDirs(model_list)
	splitMasterYaml(master_yaml_dict, model_list)
	r = callInstrument(model_list)
	return r

if __name__ == "__main__":
	if len(sys.argv[1:]) < 1 or sys.argv[1] == '--help' or sys.argv[1] == '-h':
		usage()
		sys.exit(0)
	r = main()
	sys.exit(r)