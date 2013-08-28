cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(tools)

copy(traceDiff.py traceDiff)
copy(traceOntoGraph.py traceOntoGraph)
copy(traceTools.py traceTools)
copy(traceUnion.py traceUnion)
copy(compiletoIR.py compiletoIR)

genCopy()

