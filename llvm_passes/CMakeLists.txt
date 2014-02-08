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
   Hello.cpp

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
  
  _API_NoOpenInstSelector.cpp
  _API_NoCloseInstSelector.cpp
  _API_WrongFileInstSelector.cpp
  _API_BufferOverflowInstSelector.cpp
  _API_BufferUnderflowInstSelector.cpp
  _API_WrongModeInstSelector.cpp
  _API_InappropriateCloseInstSelector.cpp
  _API_WrongPointerInstSelector.cpp
  _API_WrongRetrievedFormatInstSelector.cpp
  _API_WrongSavedFormatInstSelector.cpp

  _Mem_BufferOverflow1InstSelector.cpp
  _Mem_BufferOverflow2InstSelector.cpp
  _Mem_UnderAccumulatorInstSelector.cpp
  _Mem_WrongSourceInstSelector.cpp
  _Mem_WrongDestinationInstSelector.cpp
  _Mem_MemoryLeakInstSelector.cpp
 
  _StalePointerInstSelector.cpp
  _MemoryExhaustionInstSelector.cpp
  _InvalidPointerInstSelector.cpp
  _LowMemoryInstSelector.cpp
  _Mem_DeadLockInstSelector.cpp
  _Mem_ThreadKillerInstSelector.cpp
  _CPU_HOGInstSelector.cpp
  _Data_No_OutputInstSelector.cpp
  _API_No_OutputInstSelector.cpp 
  _Data_Incorrect_OutputInstSelector.cpp
  _API_Incorrect_OutputInstSelector.cpp
  _API_WrongAPIInstSelector.cpp
  _AutoRegSelector.cpp
  testreg.cpp
)
