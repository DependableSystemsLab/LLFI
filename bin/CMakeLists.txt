cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(bin)

copy(compile-IR.py compile-IR)
copy(create-executables.py create-executables)
copy(inject.py inject)
copy(profile.py profile)

genCopy()

