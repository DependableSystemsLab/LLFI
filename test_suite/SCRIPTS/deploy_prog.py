#! /usr/bin/env python3

import os
import sys
import shutil
import yaml
import subprocess

def deploy_prog(*prog_list):
	r = 0
	copied = 0
	suite = {}
	script_dir = os.path.dirname(os.path.realpath(__file__))
	testsuite_dir = os.path.join(script_dir, os.pardir)
	with open(os.path.join(testsuite_dir, "test_suite.yaml")) as f:
		try:
			suite = yaml.load(f)
		except:
			print("ERROR: Unable to load yaml file: test_suite.yaml", file=sys.stderr)
			return -1

	work_dict = {}
	for test in suite["SoftwareFaults"]:
		if len(prog_list) == 0 or test in prog_list or "SoftwareFaults" in prog_list:
			work_dict["./SoftwareFaults/"+test] = suite["SoftwareFaults"][test]
	for test in suite["HardwareFaults"]:
		if len(prog_list) == 0 or test in prog_list or "HardwareFaults" in prog_list:
			work_dict["./HardwareFaults/"+test] = suite["HardwareFaults"][test]
	for test in suite["BatchMode"]:
		if len(prog_list) == 0 or test in prog_list or "BatchMode" in prog_list:
			work_dict["./BatchMode/"+test] = suite["BatchMode"][test]
	
	for test_path in work_dict:
		src_dir = os.path.join(testsuite_dir, "PROGRAMS", work_dict[test_path])
		req_files = [f for f in suite["PROGRAMS"][work_dict[test_path]]]
		dst_dir = os.path.join(testsuite_dir, test_path)
		for f in req_files:
			src_path = os.path.join(src_dir, f)
			try:
				shutil.copy(src_path, dst_dir)
			except:
				print ("ERROR: Failed in copying program files:", work_dict[test_path], "for test:", test_path, file=sys.stderr)
				r += 1
			else:
				copied += 1
	print ("MSG:", copied, "files copied\n")
	return r

if __name__ == "__main__":
	r = deploy_prog(*sys.argv[1:])
	sys.exit(r)