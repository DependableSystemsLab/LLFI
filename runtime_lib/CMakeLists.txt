cmake_minimum_required(VERSION 2.8)

project(llfi-rt)

add_library(llfi-rt SHARED 
    commonfaultinjectors.cpp
    faultinjection_lib.c
    faultinjectormanager.cpp
    instTraceLib.c
    profiling_lib.c
    utils.c
)
