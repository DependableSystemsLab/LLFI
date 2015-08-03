cmake_minimum_required(VERSION 2.8)

project(llfi-rt)

add_library(llfi-rt SHARED 
    CommonFaultInjectors.cpp
    FaultInjectionLib.c
    FaultInjectorManager.cpp
    InstTraceLib.c
    ProfilingLib.c
    Utils.c
    _FIDLSoftwareFaultInjectors.cpp #_SoftwareFaultInjector.cpp is included in this file
)

add_executable(InjectorScanner
    InjectorScanner.cpp
)

TARGET_LINK_LIBRARIES(llfi-rt pthread)
TARGET_LINK_LIBRARIES(InjectorScanner llfi-rt)
