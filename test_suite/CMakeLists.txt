cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(test_suite)

copydir(HardwareFaults HardwareFaults)
copydir(SoftwareFaults SoftwareFaults)
copydir(PROGRAMS PROGRAMS)
copydir(SCRIPTS SCRIPTS)
copydir(Traces Traces)
copy(test_suite.yaml test_suite.yaml)

genCopy()

