cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(bin)

copy(instrument.py instrument)
copy(injectfault.py injectfault)
copy(profile.py profile)

genCopy()

