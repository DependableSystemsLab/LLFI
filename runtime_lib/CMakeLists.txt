cmake_minimum_required(VERSION 2.8)

project(llfi-rt)

add_library(llfi-rt SHARED 
    CommonFaultInjectors.cpp
    FaultInjectionLib.c
    FaultInjectorManager.cpp
    InstTraceLib.c
    ProfilingLib.c
    Utils.c
AutomatedInjection.cpp
IncreasedValue.cpp
DecreasedValue.cpp
noOpen_API.cpp
RevMode.cpp
WrongFormat.cpp

StalePointer.cpp
MemoryExhaustion.cpp
LowMemory.cpp
DeadLock.cpp
ThreadKiller.cpp
CPUHog.cpp
BlockedOutput.cpp

)
