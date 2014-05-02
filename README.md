LLFI
====

LLFI is an LLVM based fault injection tool, that injects faults into the LLVM IR of the application source code.  The faults can be injected into specific program points, and the effect can be easily tracked back to the source code.  LLFI is typically used to map fault characteristics back to source code, and hence understand source level or program characteristics for various kinds of fault outcomes.    

Please join the following Google Groups for information related to LLFI development: llfi-development@googlegroups.com

Dependencies
------------
  1. 32/64 bit Linux or OS X
  2. CMake (minimum v2.8)
  3. Python 3 and above
  4. Python YAML library (PyYAML)
  5. Clang v3.3
  6. LLVM v3.3, built with CMake
    * Build llvm-3.3 **WITH CMAKE** using flag `-DLLVM_REQUIRES_RTTI=1`. [Instructions](http://llvm.org/docs/CMake.html)
    * Remember to run `make` in the llvm build directory after running `cmake`.
  7. Java7 with JavaFX (For GUI)

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
  -LLVM_GXX_BIN_DIR <clang's parent dir> (optional):
      You don't need to set it if it is in system path
  -LLFI_BUILD_ROOT <path where you want to build LLFI>

--help(-h): show help information
```
Here is a sample build command if `clang` is already in $PATH:
```
./setup -LLFI_BUILD_ROOT $BUILD/LLFI -LLVM_SRC_ROOT $SRC/llvm-3.3 -LLVM_DST_ROOT $BUILD/llvm-3.3
```

Running
-------
You can use example programs in the *test_programs* directory to test LLFI, including: 
  * `min`: find the minimum number from five input numbers
  * `factorial`: compute the factorial of 6
  * `sum`: compute the sum of positive integers between 1 and N

Example program: `factorial`
  1. Go to *test_programs/. 
  2. Build a single IR file with the LLFI tool `compiletoIR`

      ```
      <LLFI_BUILD_ROOT>/tools/compiletoIR --readable -o factorial/factorial.ll factorial/factorial.c
      ```
     Alternatively, you can build your own IR file with `clang`.
  3. Instrument factorial with calls to LLFI libraries and create executables under *llfi* directory

      ```
      <LLFI_BUILD_ROOT>/bin/instrument --readable factorial/factorial.ll
      ```
  4. Run factorial executable with profiling functions instrumented

      ```
      <LLFI_BUILD_ROOT>/bin/profile factorial/llfi/factorial-profiling.exe 6
      ```
     In file *llfi/baseline/golden_std_output*, you should be able to see 720
  5. Run `factorial` executable with fault injection functions instrumented

      ```
      <LLFI_BUILD_ROOT>/bin/injectfault factorial/llfi/factorial-faultinjection.exe 6
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

GUI
====

Environment variable setup
--------------------------

1. Set the ’PYTHONPATH’ environment variable with the path of the installed Python yaml file.
     – $ open .tcshrc
     – setenv PYTHONPATH Path of Python yaml file directory
        eg: usr/Python 2.7/site-packages/
2. Create an environment variable "llfibuild" with the path of the llfi build directory.
     – $ open .tcshrc
     – setenv llfibuild Path of llfi build directory
3. Create an environment variable "COMPARE" with the path of the SDC check script.(optional)
     – $ open .tcshrc
     – setenv COMPARE Path of SDC check script
     – A sample SDC script is uploaded in /LLFI-GUI/SdcScript.sh
Running
-------
1. On setup the llfi_gui.jar file is built at LLFI-GUI/. Hence go to *LLFI-GUI/

2. Execute the jar file: java -jar llfi_gui.jar

References
----------
* [LLFI Paper](http://blogs.ubc.ca/karthik/2013/02/15/llfi-an-intermediate-code-level-fault-injector-for-soft-computing-applications/)
* [LLFI Wiki](https://github.com/DependableSystemsLab/LLFI/wiki)

======		
Read *caveats.txt* for caveats and known problems.
