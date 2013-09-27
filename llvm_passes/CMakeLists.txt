include(../config/llvm_passes.cmake)


add_llvm_loadable_module(llfi-passes
  FaultInjectionPass.cpp
  InstTracePass.cpp
  LLFIDotGraphPass.cpp
  Utils.cpp
  Controller.cpp
  FICustomSelectorManager.cpp
  FIInstSelector.cpp
  FIRegSelector.cpp
  GenLLFIIndexPass.cpp
  ProfilingPass.cpp
  InstTypeFIInstSelector.cpp
  RegLocBasedFIRegSelector.cpp
  SampleFIInstSelector.cpp
  SampleFIRegSelector.cpp
  LLFIIndexFIInstSelector.cpp
)
