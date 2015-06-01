#! /usr/bin/env python3

import os
import sys
import shutil
import yaml
import subprocess

generate_makefile_script = ''
llvm_interpreter_bin = ''

def callGenerateMakefile(work_dir, resources):
	global generate_makefile_script

	execlist = [generate_makefile_script, '--dir', work_dir]
	execlist.extend(resources['makefile_generation_args'].split(' '))
	print(' '.join(execlist))
	p = subprocess.Popen(execlist)
	p.wait()
	if p.returncode != 0:
		return ("FAIL: ERROR in calling " + generate_makefile_script + " on " + work_dir)
	else:
		return ("PASS")

def callLLVMInterpreter(work_dir, resources):
	global llvm_interpreter_bin

	cwd = os.getcwd()
	os.chdir(work_dir)
	os.system('make clean')
	os.system('make')
	prog = resources['prog']
	if 'readable' in os.path.basename(work_dir):
		prog = prog + '.ll'
	else:
		prog = prog + '.bc'

	prog = os.path.join(work_dir, prog)
	execlist = [llvm_interpreter_bin, prog]
	execlist.extend(resources['inputs'].split(' '))
	print(' '.join(execlist))
	p = subprocess.Popen(execlist)
	p.wait()
	os.chdir(cwd)

	if p.returncode != 0:
		return ("FAIL: ERROR in running on lli: " + llvm_interpreter_bin + ", test: " + work_dir)
	else:
		return ("PASS")


def test_generate_makefile(*test_list):
	global generate_makefile_script
	global llvm_interpreter_bin

	r = 0
	suite = {}
	script_dir = os.path.dirname(os.path.realpath(__file__))
	llfi_tools_dir = os.path.join(script_dir, os.pardir, os.pardir, 'tools')
	generate_makefile_script = os.path.join(llfi_tools_dir, 'GenerateMakefile')
	sys.path.append(os.path.join(script_dir, os.pardir, os.pardir, 'config'))
	import llvm_paths
	llvm_interpreter_bin = os.path.join(llvm_paths.LLVM_DST_ROOT, "bin/lli")

	testsuite_dir = os.path.join(script_dir, os.pardir)
	with open(os.path.join(testsuite_dir, "test_suite.yaml")) as f:
		try:
			suite = yaml.load(f)
		except:
			print("ERROR: Unable to load yaml file: test_suite.yaml", file=sys.stderr)
			return -1

	work_dict = {}
	for test in suite["MakefileGeneration"]:
		if len(test_list) == 0 or test in test_list or "all" in test_list:
			work_dict["./MakefileGeneration/"+test] = suite["MakefileGeneration"][test]

	result_list = []
	for test_path in work_dict:
		print ("MSG: Testing GenerateMakfile on:", test_path)
		work_dir = os.path.abspath(os.path.join(testsuite_dir, test_path))
		result = callGenerateMakefile(work_dir, work_dict[test_path])
		if result != 'PASS':
			r += 1
		else:
			result = callLLVMInterpreter(work_dir, work_dict[test_path])
			if result != 'PASS':
				r += 1
		record = {"name": test_path, "result": result}
		result_list.append(record)

	return r, result_list

if __name__ == "__main__":
	r, result_list = test_generate_makefile(*sys.argv[1:])
	print ("=============== Result ===============")
	for record in result_list:
		print(record["name"], "\t\t", record["result"])

	sys.exit(r)