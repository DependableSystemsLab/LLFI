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
  OpenCallInstSelector.cpp
  WriteCallInstSelector.cpp
  ReadCallInstSelector.cpp
  CloseCallInstSelector.cpp


   _1stOpFIRegSelector.cpp
   _2ndOpFIRegSelector.cpp
   _3rdOpFIRegSelector.cpp
   _4thOpFIRegSelector.cpp
   _RetFIRegSelector.cpp
  

   mallocInstSelector.cpp
   memcpyInstSelector.cpp
   memcmpInstSelector.cpp
   memmoveInstSelector.cpp
   freeInstSelector.cpp
  
)
