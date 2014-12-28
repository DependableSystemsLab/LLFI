LLVM Fault Injector - LLFI 
  Description: An LLVM Tool for fault injection, easily map between fault at IR and source level, configurable and extensible.

======
Pre-requisites
  1. CMake installed 
  2. LLVM version 3.4, built with CMake
  3. Python 3
  4. Python YAML library installed (PyYAML)
  5. clang-3.4 ( frontend for llvm 3.4 )
  6. Machines with 64/32 bit Linux/OS X.

======
Installation
  A. Install CMake, Python, PyYAML library

  B. Install llvm-3.4 and clang 3.4
    1. Go to "http://llvm.org/releases/download.html#3.4" to download LLVM source code and clang source code/binaries for your system.
    2. If building clang from source code, copy the source code under tools/. Access "http://llvm.org/releases/3.4/docs/GettingStarted.html#installcf" for instructions.
    2. Build llvm-3.4 ***WITH CMAKE*** 'using flag -DLLVM_REQUIRES_RTTI=1'. Access "http://llvm.org/docs/CMake.html" for instructions.
	
  C. Build LLFI
    1. Extract the code from LLFI archive (/LLFI)
    2. Go to /LLFI directory and run './setup --help' to see how to build LLFI to a different directory
	
  D. Testing LLFI
    You can use example programs in /LLFI/test_suite/PROGRAMS/factorial to test LLFI.

    Example program: factorial
      1. Copy test_suite/factorial/ to your project directory and change to that directory. 
      2. Build a single IR file with LLFI tool compiletoIR
          <LLFI_BUILD_ROOT>/tools/GenerateMakefile --readable -o factorial.ll --all
      3. Instrument factorial with calls to LLFI libraries and create executables under llfi/
          <LLFI_BUILD_ROOT>/bin/instrument --readable factorial.ll
      4. Run factorial executable with profiling functions instrumented
          <LLFI_BUILD_ROOT>/bin/profile llfi/factorial-profiling.exe 6
         In file llfi/baseline/golden_std_output, you should be able to see 720
      5. Run factorial executable with fault injection functions instrumented
          <LLFI_BUILD_ROOT>/bin/injectfault llfi/factorial-faultinjection.exe 6
         You should be able to see result files in llfi/std_output/, fault injection stats in llfi/prog_output/, failure report (crash/hang) in llfi/error_output/

======
Running LLFI on your target applications
  You can follow the same flow as the Step D of Installation (Testing LLFI). For more details, you can follow the instructions on https://github.com/DependableSystemsLab/LLFI/wiki.

======		
Read caveats.txt for caveats and known problems.
