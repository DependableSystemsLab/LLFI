#! /usr/bin/env python3

"""

%(prog)s is a test suite driver script to run all the steps of LLFI regression test. 

Usage: %(prog)s [OPTIONS]

List of options:

--threads <number of threads to use>: number of threads to be used for fault injections, default value: 1.
--all: Test all the test cases of LLFI test suite, including fault injection tests, trace analysis tests and make file generation tests.
--all_fault_injections: Test all the test cases of fault injections, including HardwareFaults, SoftwareFaults and BatchMode tests.
--all_software_faults: Test all the test cases of SoftwareFaults.
--all_hardware_faults: Test all the test cases of HardwareFaults.
--all_batchmode: Test all the test cases of BatchMode fault injections.
--all_trace_tools_tests: Test all the tests for trace analysis tools.
--all_makefile_generation: Test all the tests for makefile generation script.
--test_cases [test case names]: Test only specified test case.
--clean_after_test: Clean all the generate files after testing.

--verbose: Show verbose information
--help(-h): Show help information

"""

import sys
import os
import subprocess
import time

options = {
	'all':False,
	'all_fault_injections':False,
	'all_software_faults':False,
	'all_hardware_faults':False,
	'all_batchmode':False,
	'all_trace_tools_tests':False,
	'all_makefile_generation':False,
	'test_cases':[],
	'threads':1,
	'clean_after_test':False,
}

prog = os.path.basename(sys.argv[0])
verbose = False

def verbosePrint(msg):
	global verbose
	if verbose:
		print(msg)

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
	global verbose
	argid = 0
	while argid < len(args):
		arg = args[argid]
		
		if arg == "--all":
			options['all'] = True
			
		elif arg == "--all_fault_injections":
			options['all_fault_injections'] = True
			
		elif arg == "--all_software_faults":
			options['all_software_faults'] = True
			
		elif arg == "--all_hardware_faults":
			options['all_hardware_faults'] = True
			
		elif arg == "--all_batchmode":
			options['all_batchmode'] = True
			
		elif arg == "--test_cases":
			argid += 1
			while(argid < len(args) and args[argid][0] != '-'):
				options['test_cases'].append(str(args[argid]))
				argid += 1

		elif arg == "--threads":
			argid += 1
			options['threads'] = int(args[argid])

		elif arg == "--all_trace_tools_tests":
			options['all_trace_tools_tests'] = True

		elif arg == "--all_makefile_generation":
			options['all_makefile_generation'] = True

		elif arg == "--clean_after_test":
			options['clean_after_test'] = True

		elif arg == "--help" or arg == "-h":
			usage()

		elif arg == "--verbose":
			verbose = True

		argid += 1

def startTestRoutine():
	global options
	script_dir = os.path.dirname(os.path.realpath(__file__))
	sys.path.append(script_dir)
	build_prog_script = os.path.join(script_dir, 'build_prog.py')
	deploy_prog_script = os.path.join(script_dir, 'deploy_prog.py')
	inject_prog_script = os.path.join(script_dir, 'inject_prog.py')
	check_injection_script = os.path.join(script_dir, 'check_injection.py')
	test_trace_tools_script = os.path.join(script_dir, 'test_trace_tools.py')
	test_generate_makefile_script = os.path.join(script_dir, 'test_generate_makefile_script.py')
	clear_all_script = os.path.join(script_dir, 'clear_all.py')

	injection_result_list = []
	trace_result_list = []
	generate_makefile_result_list = []

	if options['all'] or options['all_batchmode'] or options['all_hardware_faults']\
	or options['all_software_faults'] or options['all_fault_injections']\
	or options['test_cases'] != []:
		## build all the test program
		execlist = ['python3', '-u', build_prog_script]
		verbosePrint(' '.join(execlist))
		p = subprocess.Popen(execlist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p.wait()
		r = p.returncode
		if r != 0:
			print("ERROR: Failed in building all test programs")
			sys.exit(-1)
		else:
			print("Build test programs successfully.")
	
		## deploy programs
		execlist = ['python3', '-u', deploy_prog_script]
		if options['all_batchmode']:
			execlist.append('BatchMode')
		elif options['all_software_faults']:
			execlist.append('SoftwareFaults')
		elif options['all_hardware_faults']:
			execlist.append('HardwareFaults')
		elif options['test_cases'] != []:
			execlist.extend(options['test_cases'])
		elif options['all'] or options['all_fault_injections']:
			pass
		verbosePrint(' '.join(execlist))
		p = subprocess.Popen(execlist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p.wait()
		r = p.returncode
		if r != 0:
			print("ERROR: Failed in deploy test programs")
			sys.exit(-1)
		else:
			print("Deploy test programs successfully.")

		## start fault injection
		execlist = ['python3', '-u', inject_prog_script, str(options['threads'])]
		if options['all_batchmode']:
			execlist.append('BatchMode')
		elif options['all_software_faults']:
			execlist.append('SoftwareFaults')
		elif options['all_hardware_faults']:
			execlist.append('HardwareFaults')
		elif options['test_cases'] != []:
			execlist.extend(options['test_cases'])
		elif options['all'] or options['all_fault_injections']:
			pass
		verbosePrint(' '.join(execlist))
		p = subprocess.Popen(execlist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p.wait()
		r = p.returncode
		if r != 0:
			print("WARNING: error occurs during fault injection. Continue on testing.")
		else:
			print("Fault injection ends normally.")

		## check the injection
		import check_injection
		prog_list = []
		if options['all_batchmode']:
			prog_list.append('BatchMode')
		elif options['all_software_faults']:
			prog_list.append('SoftwareFaults')
		elif options['all_hardware_faults']:
			prog_list.append('HardwareFaults')
		elif options['test_cases'] != []:
			prog_list.extend(options['test_cases'])
		elif options['all'] or options['all_fault_injections']:
			pass
		verbosePrint('Calling: check_injection.check_injection(' + ' '.join(prog_list) + ')')
		check_injection_returncode, injection_result_list = check_injection.check_injection(*prog_list)

	## run trace tools's tests
	if options['all_trace_tools_tests'] or options['all'] or options['test_cases'] != []:
		import test_trace_tools
		prog_list = []
		if options['test_cases'] != []:
			prog_list.extend(options['test_cases'])
		elif options['all_trace_tools_tests'] or options['all']:
			pass
		verbosePrint('Calling: test_trace_tools.test_trace_tools(' + ' '.join(prog_list) + ')')
		test_trace_tools_returncode, trace_result_list = test_trace_tools.test_trace_tools(*prog_list)

	## run MakefileGeneration tests
	if options['all_makefile_generation'] or options['all'] or options['test_cases'] != []:
		import test_generate_makefile
		prog_list = []
		if options['test_cases'] != []:
			prog_list.extend(options['test_cases'])
		elif options['all_makefile_generation'] or options['all']:
			pass
		verbosePrint('Calling: test_generate_makefile.test_generate_makefile(' + ' '.join(prog_list) + ')')
		test_generate_makefile_returncode, generate_makefile_result_list = test_generate_makefile.test_generate_makefile(*prog_list)

	## collect the results
	total = 0
	passed = 0
	if len(injection_result_list) > 0:
		print ("==== Check Injection Result ====")
		for record in injection_result_list:
			print(record["name"], "\t\t", record["result"])
			total += 1
			if record['result'] == 'PASS':
				passed += 1
	if len(trace_result_list) > 0:
		print ("==== Test Trace Tools Result ====")
		for record in trace_result_list:
			print(record["name"], "\t\t", record["result"])
			total += 1
			if record['result'] == 'PASS':
				passed += 1

	if len(generate_makefile_result_list) > 0:
		print("==== Test MakefileGeneration Tool Result ====")
		for record in generate_makefile_result_list:
			print(record["name"], '\t\t', record["result"])
			total += 1
			if record['result'] == 'PASS':
				passed += 1

	print("=== Overall Counts ====")
	print("Total tests:\t", total)
	print("Passed tests:\t", passed)
	print("Failed tests:\t", total - passed)

	if options['clean_after_test']:
		execlist = ['python3', '-u', clear_all_script]
		verbosePrint(' '.join(execlist))
		p = subprocess.Popen(execlist, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p.wait()
		os.chdir(os.path.join(script_dir, os.pardir, 'PROGRAMS'))
		os.system('make clean')
		dirs = [d for d in os.listdir(os.path.join(script_dir, os.pardir, 'MakefileGeneration')) 
		if os.path.isdir(os.path.join(script_dir, os.pardir, 'MakefileGeneration',d))]
		print(dirs)
		for d in dirs:
			p = os.path.join(script_dir, os.pardir, 'MakefileGeneration', d)
			os.chdir(p)
			os.system('make clean')


	return 0

if __name__ == "__main__":
	if len(sys.argv) == 1:
		usage()
	parseArgs(sys.argv[1:])
	print("Tests Start on: ", time.ctime())
	r = startTestRoutine()
	print("Tests Ends on: ", time.ctime())
	sys.exit(r)
