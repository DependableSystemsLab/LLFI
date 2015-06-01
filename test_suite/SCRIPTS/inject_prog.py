#! /usr/bin/env python3

import os
import sys
import shutil
import yaml
import subprocess
import time
from threading  import Thread

try:
	from Queue import Queue, Empty
except ImportError:
	from queue import Queue, Empty  # python 3.x
ON_POSIX = 'posix' in sys.builtin_module_names

instrument_script = ""
profile_script = ""
injectfault_script = ""
batchinstrument_script = ""
batchprofile_script = ""
batchinjectfault_script = ""
autoscan_script = ""

def enqueue_output(out, queue):
	for line in iter(out.readline, b''):
		queue.put(line)
	out.close()

def startEchoServer(work_dir):
	print("using startEchoServer")
	execlist = ["stdbuf", '-i0', '-o0', '-e0']
	execlist.extend([os.path.join(work_dir, "echoServer.exe")])
	server = subprocess.Popen(execlist, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	q = Queue()
	t = Thread(target=enqueue_output, args=(server.stdout, q))
	t.daemon = True # thread dies with the program
	t.start()
	count = 0
	while server.poll() == None:
		if count > 50:
			server.terminate()
			return startEchoServer(work_dir)
		try:  line = q.get_nowait() # or q.get(timeout=.1)
		except Empty:
			print('no output yet')
			count += 1
			time.sleep(1)
		else: 
			print (line)
			line = str(line)
			if "Server running...waiting for connections." in line:
				return server
			else:
				count += 1
				time.sleep(1)

def callLLFI(work_dir, target_IR, prog_input):
	global instrument_script
	global profile_script
	global injectfault_script

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
			print ("MSG: instrument succeed for:", work_dir, target_IR)

	with open("llfi.test.log.profile.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = startEchoServer(work_dir)
			print ("MSG: echoServer.ll started for profile, please make sure there is only one echoServer running\n")
			time.sleep(2)
		profile_exe = target_IR.split(".ll")[0]+"-profiling.exe"
		execlist = [profile_script, "./llfi/"+profile_exe]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		p.wait()
		if target_IR == "echoClient.ll":
			try:
				server.terminate()
				print ("MSG: echoServer.exe terminated for profile.\n")
			except:
				print ("ERROR: Unable to terminate echoServer.exe in profile for:", work_dir)
		if p.returncode != 0:
			print ("ERROR: profile failed for:", work_dir, target_IR)
			return -1, None
		else:
			print ("MSG: profile succeed for:", work_dir, target_IR, prog_input)

	with open("llfi.test.log.injectFault.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = startEchoServer(work_dir)
			print ("MSG: echoServer.ll started for injectfault, please make sure there is only one echoServer running\n")
			time.sleep(2)
		faultinjection_exe = target_IR.split(".ll")[0]+"-faultinjection.exe"
		execlist = [injectfault_script, "./llfi/"+faultinjection_exe]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		t = {"name":' '.join(work_dir.split('/')[-3:])+"/"+target_IR,
			"process":p}
		if target_IR == "echoClient.ll":
			p.wait()
			try:
				server.terminate()
				print ("MSG: echoServer.exe terminated for profile.\n")
			except:
				print ("ERROR: Unable to terminate echoServer.exe in injectfault for", work_dir)
			
	return 0, t

def callBatchLLFI(work_dir, target_IR, prog_input):
	global batchinstrument_script
	global batchprofile_script
	global batchinjectfault_script
	global autoscan_script

	try:
		os.chdir(work_dir)
	except:
		print ("ERROR: Unable to change directory to:", work_dir)
		return -1, None

	if 'SoftwareFailureAutoScan' in os.path.basename(work_dir):
		with open("llfi.test.log.SoftwareFailureAutoScan.txt", 'w', buffering=1) as log:
			p = subprocess.Popen([autoscan_script, target_IR], stdout=log, stderr=log)
			p.wait()
			if p.returncode != 0:
				print ("ERROR: SoftwareFailureAutoScan failed for:", work_dir, target_IR)
				return -1, None
			else:
				print ("MSG: SoftwareFailureAutoScan succeed for:", work_dir, target_IR)

	with open("llfi.test.log.instrument.txt", 'w', buffering=1) as log:
		p = subprocess.Popen([batchinstrument_script, "--readable", "-lpthread", target_IR], stdout=log, stderr=log)
		p.wait()
		if p.returncode != 0:
			print ("ERROR: batchInstrument failed for:", work_dir, target_IR)
			return -1, None
		else:
			print ("MSG: batchInstrument succeed for:", work_dir, target_IR)

	with open("llfi.test.log.profile.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = startEchoServer(work_dir)
			print ("MSG: echoServer.ll started for profile, please make sure there is only one echoServer running\n")
			time.sleep(2)
		execlist = [batchprofile_script, target_IR]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		p.wait()
		if target_IR == "echoClient.ll":
			try:
				server.terminate()
				print ("MSG: echoServer.exe terminated for profile.\n")
			except:
				print ("ERROR: Unable to terminate echoServer.exe in profile for:", work_dir)
		if p.returncode != 0:
			print ("ERROR: profile failed for:", work_dir, target_IR)
			return -1, None
		else:
			print ("MSG: profile succeed for:", work_dir, target_IR, prog_input)

	with open("llfi.test.log.injectFault.txt", 'w', buffering=1) as log:
		if target_IR == "echoClient.ll":
			server = startEchoServer(work_dir)
			print ("MSG: echoServer.ll started for injectfault, please make sure there is only one echoServer running\n")
			time.sleep(2)
		execlist = [batchinjectfault_script, target_IR]
		execlist.extend(prog_input.split(' '))
		p = subprocess.Popen(execlist, stdout=log, stderr=log)
		t = {"name":' '.join(work_dir.split('/')[-3:])+"/"+target_IR,
			"process":p}
		if target_IR == "echoClient.ll":
			p.wait()
			try:
				server.terminate()
				print ("MSG: echoServer.exe terminated for profile.\n")
			except:
				print ("ERROR: Unable to terminate echoServer.exe in injectfault for", work_dir)
			
	return 0, t

def inject_prog(num_threads, *prog_list):
	global instrument_script
	global profile_script
	global injectfault_script
	global batchinstrument_script
	global batchprofile_script
	global batchinjectfault_script
	global autoscan_script

	r = 0
	suite = {}
	script_dir = os.path.dirname(os.path.realpath(__file__))
	llfi_bin_dir = os.path.join(script_dir, '../../bin')
	instrument_script = os.path.join(llfi_bin_dir, "instrument")
	profile_script = os.path.join(llfi_bin_dir, "profile")
	injectfault_script = os.path.join(llfi_bin_dir, "injectfault")
	batchinstrument_script = os.path.join(llfi_bin_dir, "batchInstrument")
	batchprofile_script = os.path.join(llfi_bin_dir, "batchProfile")
	batchinjectfault_script = os.path.join(llfi_bin_dir, "batchInjectfault")
	autoscan_script = os.path.join(llfi_bin_dir, "SoftwareFailureAutoScan")
	
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
		if test_path.startswith('./BatchMode'):
			code, t = callBatchLLFI(inject_dir, inject_prog, inject_input)
		else:
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
