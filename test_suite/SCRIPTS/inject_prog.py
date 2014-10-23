#! /usr/bin/env python3

import os
import sys
import shutil
import yaml
import subprocess

instrument_script="instrument"
profile_script="profile"
injectfault_script="injectfault"

def callLLFI(work_dir, target_IR, prog_input):
	try:
		os.chdir(work_dir)
	except:
		print ("ERROR: Unable to change directory to:", work_dir)
		return -1, None
	with open("llfi.test.log.instrument.txt", 'w', buffering=1) as log:
		p = subprocess.Popen([instrument_script, "--readable", "-lpthread", target_IR], stdout=log, stderr=log)
		p.wait()
		if p.returncode != 0:
			print ("ERROR: instrument failed for:", work_dir, target_IR)
			return -1, None
		else:
			print ("MSG: instrument successed for:", work_dir, target_IR)

	with open("llfi.test.log.profile.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = subprocess.Popen(["lli", os.path.join(work_dir, "echoServer.ll")], stdout=log, stderr=log)
		profile_exe = target_IR.split(".ll")[0]+"-profiling.exe"
		execlist = [profile_script, '--CLI', "./llfi/"+profile_exe]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		p.wait()
		if target_IR == "echoClient.ll":
			try:
				server.terminate()
			except:
				print ("ERROR: Unable to terminate echoServer.ll in profile for:", work_dir)
		if p.returncode != 0:
			print ("ERROR: profile failed for:", work_dir, target_IR)
			return -1, None
		else:
			print ("MSG: profile successed for:", work_dir, target_IR, prog_input)

	with open("llfi.test.log.injectFault.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = subprocess.Popen(["lli", os.path.join(work_dir, "echoServer.ll")], stdout=log, stderr=log)
		faultinjection_exe = target_IR.split(".ll")[0]+"-faultinjection.exe"
		execlist = [injectfault_script, '--CLI', "./llfi/"+faultinjection_exe]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		t = {"name":' '.join(work_dir.split('/')[-3:])+"/"+target_IR,
			"process":p}
		if target_IR == "echoClient.ll":
			p.wait()
			try:
				server.terminate()
			except:
				print ("ERROR: Unable to terminate echoServer.ll in injectfault for", work_dir)
			
	return 0, t


def inject_prog(num_threads, *prog_list):
	r = 0
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
	
	running_list = []
	exitcode_list = []
	for test_path in work_dict:
		while(len(running_list) >= num_threads):
			for t in running_list:
				if t["process"].poll() is None:
					continue
				else:
					print ("MSG: Injection for:", t["name"], "finished!\n")
					running_list.remove(t)
					record={"name":t["name"], "exitcode":t["process"].returncode}
					exitcode_list.append(record)

		inject_dir = os.path.abspath(os.path.join(testsuite_dir, test_path))
		inject_prog = suite["PROGRAMS"][work_dict[test_path]][0]
		inject_input = str(suite["INPUTS"][work_dict[test_path]])
		code, t = callLLFI(inject_dir, inject_prog, inject_input)
		if code != 0:
			print ("ERROR: Skip:", test_path)
			continue
		running_list.append(t)

	while(len(running_list) > 0):
		for t in running_list:
			if t["process"].poll() is None:
				continue
			else:
				print ("MSG: Injection for:", t["name"], "finished!\n")
				running_list.remove(t)
				record={"name":t["name"], "exitcode":t["process"].returncode}
				exitcode_list.append(record)
	return r

if __name__ == "__main__":
	r = inject_prog(int(sys.argv[1]), *sys.argv[2:])
	sys.exit(r)