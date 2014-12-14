cmake_minimum_required(VERSION 2.8)

option(NO_GUI "Skip building GUI" OFF)

add_subdirectory(llvm_passes)
add_subdirectory(runtime_lib)
add_subdirectory(bin)
add_subdirectory(tools)
add_subdirectory(config)
add_subdirectory(test_suite)

if(NOT NO_GUI)
	add_subdirectory(gui)
endif