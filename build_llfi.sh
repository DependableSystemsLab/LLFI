#!/bin/bash

########## FILL THESE OUT ########

SRC=${HOME}/src
BUILD=${HOME}/build

LLFI_BUILD=${BUILD}/llfi

LLVM_SRC=${SRC}/llvm-3.3
LLVM_BUILD=${BUILD}/llvm-3.3

##################################

echo "Building LLFI"

# Ensure LLFI build directory does not exist
rm -rf ${LLFI_BUILD}

# Run LLFI setup
./setup -LLFI_BUILD_ROOT ${LLFI_BUILD} -LLVM_SRC_ROOT ${LLVM_SRC} -LLVM_DST_ROOT ${LLVM_BUILD}

