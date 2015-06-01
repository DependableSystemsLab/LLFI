#! /usr/bin/env python3

import os
import sys
import shutil
import yaml

def clear_all():
	suite = {}
	script_dir = os.path.dirname(os.path.realpath(__file__))
	testsuite_dir = os.path.join(script_dir, os.pardir)
	with open(os.path.join(testsuite_dir, "test_suite.yaml")) as f:
		try:
			suite = yaml.load(f)
		except:
			print("ERROR: Unable to load yaml file: test_suite.yaml", file=sys.stderr)
			return -1

	## clear hardware faults
	for test in suite["HardwareFaults"]:
		fs = [f for f in os.listdir(os.path.join(testsuite_dir, "HardwareFaults", test))]
		for f in fs:
			if f != "input.yaml":
				print("MSG: Removing ", "HardwareFaults/"+test+"/"+f)
				if os.path.isdir(os.path.join(testsuite_dir, "HardwareFaults", test, f)):
					shutil.rmtree(os.path.join(testsuite_dir, "HardwareFaults", test, f))
				else:
					os.remove(os.path.join(testsuite_dir, "HardwareFaults", test, f))

	## clear software faults
	for test in suite["SoftwareFaults"]:
		fs = [f for f in os.listdir(os.path.join(testsuite_dir, "SoftwareFaults", test))]
		for f in fs:
			if f != "input.yaml":
				print("MSG: Removing ", "SoftwareFaults/"+test+"/"+f)
				if os.path.isdir(os.path.join(testsuite_dir, "SoftwareFaults", test, f)):
					shutil.rmtree(os.path.join(testsuite_dir, "SoftwareFaults", test, f))
				else:
					os.remove(os.path.join(testsuite_dir, "SoftwareFaults", test, f))

	## clear batch mode faults
	for test in suite["BatchMode"]:
		fs = [f for f in os.listdir(os.path.join(testsuite_dir, "BatchMode", test))]
		for f in fs:
			if f != "input.yaml":
				print("MSG: Removing ", "BatchMode/"+test+"/"+f)
				if os.path.isdir(os.path.join(testsuite_dir, "BatchMode", test, f)):
					shutil.rmtree(os.path.join(testsuite_dir, "BatchMode", test, f))
				else:
					os.remove(os.path.join(testsuite_dir, "BatchMode", test, f))
	
	return 0

if __name__ == "__main__":
	r = clear_all()
	sys.exit(r)