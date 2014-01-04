LLFI
====

LLFI is an LLVM based fault injection tool, that injects faults into the LLVM IR of the application source code.  The faults can be injected into specific program points, and the effect can be easily tracked back to the source code.  LLFI is typically used to map fault characteristics back to source code, and hence understand source level or program characteristics for various kinds of fault outcomes.    Please refer to paper below for more details: Anna Thomas, Karthik Pattabiraman, LLFI: An Intermediate code-level fault injector, in Pacific Rim International Symposium on Dependable Computing (PRDC), Fast abstract, 2012

Dependencies
------------
  1. 32/64 bit Linux or OS X
  2. CMake
  3. Python
  4. Python YAML library (PyYAML)
  5. llvm-gcc 4.2.1 (front end for LLVM 2.9).
    * [Download](http://llvm.org/releases/download.html#2.9) llvm-gcc 4.2 front end binaries for your system. **OR**
    * Build llvm-gcc 4.2 for your system. [Instructions](http://llvm.org/releases/2.9/docs/GettingStarted.html#installcf)
  6. LLVM version 2.9, built with CMake
    1. Build llvm-2.9 **WITH CMAKE**. [Instructions](http://llvm.org/docs/CMake.html)
      * Remember to run `make` in the llvm build directory after running `cmake` specified in the instructions

Building
--------
Run `./setup --help` for build instructions.
```
$ ./setup --help

Usage: setup OPTIONS
List of options:
  -LLVM_DST_ROOT <LLVM CMake build root dir>:
      Make sure you build LLVM with CMake and pass build root directory here
  -LLVM_SRC_ROOT <LLVM source root dir>
  -LLVM_GXX_BIN_DIR <llvm-gcc/g++'s parent dir> (optional):
      You don't need to set it if it is in system path
  -LLFI_BUILD_ROOT <path where you want to build LLFI>

--help(-h): show help information
```
Here is a sample build command if `llvm-gcc` is already in $PATH:
```
./setup -LLFI_BUILD_ROOT $BUILD/LLFI -LLVM_SRC_ROOT $SRC/llvm-2.9 -LLVM_DST_ROOT $BUILD/llvm-2.9
```

Running
-------
You can use example programs in the *test_programs* directory to test LLFI, including: 
  * `min`: find the minimum number from five input numbers
  * `factorial`: compute the factorial of 6
  * `sum`: compute the sum of positive integers between 1 and N

Example program: `factorial`
  1. Go to *test_programs/factorial*. 
  2. Build a single IR file with the LLFI tool `compiletoIR`

      ```
      <LLFI_BUILD_ROOT>/tools/compiletoIR --readable -o factorial.ll factorial.c
      ```
     Alternatively, you can build your own IR file with `llvm-gcc`.
  3. Instrument factorial with calls to LLFI libraries and create executables under *llfi* directory

      ```
      <LLFI_BUILD_ROOT>/bin/instrument --readable factorial.ll
      ```
  4. Run factorial executable with profiling functions instrumented

      ```
      <LLFI_BUILD_ROOT>/bin/profile llfi/factorial-profiling.exe 6
      ```
     In file *llfi/baseline/golden_std_output*, you should be able to see 720
  5. Run `factorial` executable with fault injection functions instrumented

      ```
      <LLFI_BUILD_ROOT>/bin/injectfault llfi/factorial-faultinjection.exe 6
      ```

Results
-------
After fault injection, output from LLFI and the tested application can be found
in the *llfi* directory.

|     Directory      |                 Contents                       |
| ------------------ | ---------------------------------------------- |
| *std_output*       | Piped STDOUT from the tested application       |
| *llfi_stat_output* | Fault injection statistics                     |
| *error_output*     | Failure reports (program crashes, hangs, etc.) |


References
----------
* [LLFI Paper](http://blogs.ubc.ca/karthik/2013/02/15/llfi-an-intermediate-code-level-fault-injector-for-soft-computing-applications/)
* [LLFI Wiki](https://github.com/DependableSystemsLab/LLFI/wiki)

======		
Read *caveats.txt* for caveats and known problems.
