LLVM Fault Injector - LLFI 
Description: An LLVM Tool for fault injection, easily map between fault at IR and source level.

Pre-requisites
1. llvm version 2.9
2. 64 bit linux machines with GCC or 32 bit linux machines with GCC 4.4.5
3. Perl
4. llvm-gcc 4.2.1 ( frontend for llvm 2.9 )
5. Time-out-0.11 package for Perl

Installation
A. Install Time-out-0.11 package for Perl (http://search.cpan.org/~patl/Time-Out-0.11/)
	1. Extract the files in Time-out-0.11.tar.gz and place them under your ~/Time-out-0.11.
	2. Read the Readme file in Time-out-0.11, follow the instructions to install the package.
	
B. Install llvm-2.9 and llvm-gcc 4.2.1
	1. Go to "http://llvm.org/releases/download.html#2.9" to download LLVM source code and LLVM-GCC 4.2 Front End Binaries for your system.
	2. Install llvm-gcc 4.2 for your system. Access "http://llvm.org/releases/2.9/docs/GettingStarted.html#installcf" for instructions.
	3. Install llvm-2.9. Access "http://llvm.org/releases/2.9/docs/GettingStarted.html" for instructions.
	4. We use $LLVMSRC to represent  the root directory of your llvm source code(usually /llvm ) and $LLVMOBJ for the root directory of your llvm build stuff (usually /build ).
	
C. Build LLFI libraries
	1. Extract the code from LLFI archive (/LLFI)
	2. Copy the content under LLFI/src/ (excluding 'LLFI/src/') into your $LLVMSRC/lib/Transforms,  
	3. copy the content under LLFI/dst to your $LLVMOBJ/lib/Transforms 
	4. Under directory "$LLVMOBJ/lib/Transforms/LLFI/faultinjection/", do make.
	5. Under directory "$LLVMOBJ/lib/Transforms/LLFI/profiling/", do make
	6. You should be able to find "LLFI.so" and "LLFIProfiling.so" under "$LLVMOBJ/<your_llvm_build>/lib/". (Eg: ~/llvm/build/Release/lib/)
	
D. Testing LLFI
	You can use example programs in /LLFI/test_programs folder to test LLFI, including: 
		"min"--find the minimum number from five input numbers
		"factorial" --compute the factorial of 6

	Example program: factorial
	1. Copy /LLFI/test_programs/factorial to your $LLVMOBJ/projects (or anywhere else you usually place your test programs). 
	2. Build linked .bc file: factorial.bc through llvm-gcc.
	3. Execute "./run_all.sh factorial input.factorial $LLVMOBJ/<your_llvm_build>/lib/ 10" 
		in $OBJ/projects/factorial. For example: $LLVMOBJ/<your_llvm_build>/lib/ can be ~/llvm/Release/lib/ 
	4. You should be able to see "id:count = ##:##", "size_byte=#  address=0x########  bytepos=# ....".

Running LLFI on your target applications
LLFI/faultinjection_scripts contains the perl, shell scripts to run the fault injector and C library for fault injection. 
The perl script (faultinject.pl) runs the fault injector (assumption is text files, so you will need to use your own scripts or modify the perl script for storing the output files). 
	A. Preparation
		1. Copy the content under LLFI/faultinjection_scripts to your target program working directory.
		2. Make sure you have the final executable bitcode file (file.bc) for your target program.
		3. Create an input file to hold the command line arguments for target application. 
		4. Following instructions use "appName" to represent your target program, 
		   "input.appName" for the input file, 
		   "num_injection" for the number of injection tests.
	
	B. Injection 
		1. Change to your test program directory. 
		2. Execute ./run_all.sh <appName> <input.appName> $LLVMOBJ/<your_llvm_build>/lib/ <num_injection>
		3. If LLFI is working well, you should be able to see "id:count = ##:##", "size_byte=#  address=0x########  bytepos=# ....".
		
	C. Output Files for analysis
		1. File "appName.mem2reg.bc.activatedFaults.txt" records the faults have been injected and activated ( the activation rate should be 100% ). 
			"ID" means the id of fault injection instruction which has been activated in this execution, 
				it indicates the static location where a fault occured. 
			"size" indicate the size of data (in bits) which has been corrupted by the fault. 
			"old" means the original value of the corrupted datum. 
			"new" means the new value of the corrupted datum. 
			"count" means the dynamic location where the fault occured.
		
		2. File "appName_faultoutcome_stats.txt" classifies the results of the fault-injected program into Crash, Hang, SDC and Benign four types. 
			"SDC INDEX" indicates which time of injection resulted in SDC. It is different from the "ID" mentioned in C. Ouput section above.
			"CRASH INDEX" indicates which time of injection resulted in Crash.
			"BENIGN INDEX" and "HANG INDEX" same as SDC and Crash index.
			"SDC Rate with 100% activation: " shows how many injections resulted in SDC
			"APPLICATION, SDC, CRASH, BENIGN, HANG"
			"appName,      ##,      ##,      ##,       ##" This table shows how many injections resulted in each type of results.
			"ALL SDC" shows the ID of the fault-injection-instruction been activated which cause the SDC result. 
				This ID is the same one mentioned in C.Output section.
			"ALL CRASH" shows the ID of the fault-injection-instruction been activated which cause the crash result.
			"ALL BENIGN" and "ALL HANG" same as all crash and all SDC.
			
		3. File "appName.final_inject.bs.bc" is the final bitcode file with fault-injection-instruction instrumented. 		
		4. Folder "appName_baseline". This folder is used to store the correct outputs of the target program(with out fault injection). 
		5. Folder "appName_output_BackwardSlice". This folder is used to store the outputs of the target program after being injected with one fault. The names of its files correspond to each fault injection run. 
		
Read caveats.txt for caveats and known problems.
