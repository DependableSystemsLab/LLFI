cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(tools)

copy(tracediff.py tracediff)
copy(compiletoIR.py compiletoIR)
copy(traceontograph.py traceontograph)
copy(tracetodot.py tracetodot)
copy(tracetools.py tracetools.py)
copy(traceunion.py traceunion)
copy(GenerateMakefile.py GenerateMakefile)

copy(zgrviewer/llfi_run.sh zgrviewer/run.sh)

#FIDL tests
copydir(FIDL/tests/ FIDL/tests/)

genCopy()
