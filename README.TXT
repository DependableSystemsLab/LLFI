LLVM Fault Injector - LLFI 
  Description: An LLVM Tool for fault injection, easily map between fault at IR and source level, configurable and extensible.

======
Pre-requisites
  1. CMake installed 
  2. LLVM version 2.9, built with CMake
  3. Python
  4. Python YAML library installed (PyYAML)
  5. llvm-gcc 4.2.1 ( frontend for llvm 2.9 )
  6. Machines with 64/32 bit Linux/OS X.

======
Installation
  A. Install CMake, Python, PyYAML library

  B. Install llvm-2.9 and llvm-gcc 4.2.1
    1. Go to "http://llvm.org/releases/download.html#2.9" to download LLVM source code and LLVM-GCC 4.2 Front End Binaries for your system.
    2. Build llvm-gcc 4.2 for your system. Access "http://llvm.org/releases/2.9/docs/GettingStarted.html#installcf" for instructions.
    3. Build llvm-2.9 *** WITH CMAKE ***. Access "http://llvm.org/docs/CMake.html" for instructions. Remember to run 'make' in the llvm build directory after running 'cmake' specified in the instructions
	
  C. Build LLFI
    1. Extract the code from LLFI archive (/LLFI)
    2. Go to /LLFI directory and run './setup --help' to see how to build LLFI to a different directory
	
  D. Testing LLFI
    You can use example programs in /LLFI/test_programs folder to test LLFI, including: 
      "min"--find the minimum number from five input numbers
      "factorial" --compute the factorial of 6

    Example program: factorial
      1. Go to test_programs/factorial. 
      2. Build a single IR file with LLFI tool compiletoIR
          <LLFI_BUILD_ROOT>/tools/compiletoIR --readable -o factorial.ll factorial.c
      3. Instrument factorial with calls to LLFI libraries and create executables under llfi/
          <LLFI_BUILD_ROOT>/bin/instrument --readable factorial.ll
      4. Run factorial executable with profiling functions instrumented
          <LLFI_BUILD_ROOT>/bin/profile llfi/factorial-profiling.exe 6
         In file llfi/baseline/golden_std_output, you should be able to see 720
      5. Run factorial executable with fault injection functions instrumented
          <LLFI_BUILD_ROOT>/bin/injectfault llfi/factorial-faultinjection.exe 6
         You should be able to see result files in llfi/std_output/, fault injection stats in llfi/llfi_stat_output/, failure report (crash/hang) in llfi/error_output/

======
Running LLFI on your target applications
  You can follow the same flow as the Step D of Installation (Testing LLFI). For more details, you can follow the instructions on https://github.com/DependableSystemsLab/LLFI/wiki.

======		
Read caveats.txt for caveats and known problems.
