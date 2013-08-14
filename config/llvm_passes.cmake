# TODO: support installed LLVM and LLFI installation

cmake_minimum_required(VERSION 2.8)

include(../config/llvm_paths.cmake)
set(LLVM_ON_UNIX 1)

if (NOT EXISTS ${LLVM_DST_ROOT}/include/llvm)
  message(FATAL_ERROR "LLVM_DST_ROOT (${LLVM_DST_ROOT}) is not a valid LLVM build")
endif()

set(LLVM_INCLUDE_DIRS ${LLVM_DST_ROOT}/include ${LLVM_SRC_ROOT}/include)
set(LLVM_LIBRARY_DIRS ${LLVM_DST_ROOT}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_DST_ROOT}/share/llvm/cmake")

include(LLVM)
include(AddLLVM)

add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-D__STDC_LIMIT_MACROS)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
