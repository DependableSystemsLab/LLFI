Patch for configurable LLFI
Description: 
A patch to enable LLFI to be configurable for injecting to a limitted variables used for specific function calls.
This version of configurable LLFI is self-contained, all required original LLFI contents are either included or modified.

Please read README.TXT for LLFI before reading this text.

Configure fault injection:
Before running LLFI, modify or create the file "llfi_configure.txt"
Below is an example of the content of "llfi_configure.txt".
*****************Content llif_configure.txt*****************
FUNCTION_NAME:packet_put_cstring
ARGUMENT: 1 <BYTE>
ARGUMENT: 2 <BIT>
ARGUMENT: 3 <BIT>
ARGUMENT: 4 
ARGUMENT: 5 <BYTE>
FUNC_DEF_END

FUNCTION_NAME:socket
FUNC_DEF_END

FUNCTION_NAME:connect
ARGUMENT: 1 <BYTE>
ARGUMENT: 4 
ARGUMENT: 5 <BIT>
FUNC_DEF_END
*****************End of  llif_configure.txt*****************
"FUNCTION_NAME:" should be followed with the function name we want to consider for fault injection.
"FUNC_DEF_END" means the end of configuration for the last function
"ARGUMENT:" between a pair of "FUNCTION_NAME:" and "FUNC_DEF_END" is a configuration for the function specified by the function name .
"ARGUMENT: 2 <BIT>" means the second argument of the specific function is a candidate for one bit filp fault injection
"ARGUMENT: 5 <BYTE>" means the fifth argument of the function is a candidate for whole byte fault injection.
"ARGUMENT: 4" means the sixth argument of the function is a candidate for default type fault injection. Currently, the default type is one bit filp.
If the argument number defined in llif_configure.txt beyond the arguments the function has, the descriiption line won't make any effects.
If there is no argument description for one function described in llfi_configure.txt, all arguments of the function will be considered as candidate for default type fault injection. Currently, one bit filp is the default type.
If this file is not found in current directory or the content doesn't match this format, all instructions of the application will be candidates for injection, this LLFI will work as the unconfigurable LLFI (original LLFI) 

Most parts of this LLFI are the same with the original LLFI, only differences are explained here.

Differences in Installation:
D. Testing LLFI
	You can use example programs in /LLFI/test_programs folder to test LLFI_configurble, including: 
		"ssh" --ssh program compiled from openSSH by llvm-gcc for llvm use

	Example program: ssh
	1. Copy /LLFI/test_programs/ssh to your $LLVMOBJ/projects (or anywhere else you usually place your test programs). 
	2. Build linked .bc file: ssh.bc through llvm-gcc. (Already provided in /LLFI/test_programs/ssh)
	3. Execute "./run_all.sh ssh input.ssh $LLVMOBJ/<your_llvm_build>/lib/ 10" 
		in $OBJ/projects/factorial. For example: $LLVMOBJ/<your_llvm_build>/lib/ can be ~/llvm/Release/lib/ 
	4. You should be able to see "The func_name is XXXX...... 0 is a XXXX, 1 is a XXXX......".

Running LLFI_configurable on your target applications
LLFI/faultinjection_scripts contains the perl, shell scripts to run the fault injector and C library for fault injection. 
The perl script (faultinject.pl) runs the fault injector (assumption is text files, so you will need to use your own scripts or modify the perl script for storing the output files). 
The perl script "faultoutcomes.pl" classifies the result into CRASH, SDC, TIMEOUT, BENIGN. The rule for judging depends on the target application. You may need to modify the script for your application.
Following instructions use "appName" to represent your target program, 
 "input.appName" for the input file, 
	A. Preparation
		1. Copy the content under LLFI/faultinjection_scripts to your target program working directory.
		2. Use llvm-gcc -emit-llvm to compile your application and use llvm-ld to link them. appName.bc --bitcode file, and appName --script using lli will be generated
		3. Create an input file "input.appName" to hold the command line arguments for target application. 
		4. Modify "llfi_configure.txt" to specify target functions(function names), target arguments(argument positions) and fault type(bit flip or whole byte error)
		5. IF the target application NEEDS external dynamic libraries, or we want to test an interactive application automatically, a script to run it will be required:
				Create "test_baseline.sh", "test_fi.sh","test_prof.sh" which can start a thread for: 
				lli -load=<external libraries used in the application makefile> appName.bc/appName.final_prof.bs.bc/appName.final_inject.bs.bc <input command>
				The effective input command is the one wrote in above scripts, input.appName is useless here, but it is needed to run LLFI correctly. So make sure there is one file named input.appName.
				The external libraries load string can also be found in "appName" -- a script generated after using llvm-ld for linking the bitcode files.
				To run application automatically, we can use Expect in these three scripts.
				Modify "faultinject.pl" to make sure LLFI run these three script when we run for baseline, profiling and injection.
		   IF the target application doesn't need external dynamic libraries, and the application doesn't need manual operation during execution:
				Make sure "input.appName" contains the input commands
				Modify "faultinject.pl" to make LLFI run "lli appName.bc/appName.final_prof.bs.bc/appName.final_inject.bs.bc" instead of scripts.
