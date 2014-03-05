cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(config)

copy(__init__.py __init__.py)
copy(llvm_paths.py llvm_paths.py)

genCopy()

