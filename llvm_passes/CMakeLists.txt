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

    
    
  _API_NoOpenInstSelector.cpp
  _API_NoCloseInstSelector.cpp
  _API_Incorrect_OutputInstSelector.cpp
  _API_No_OutputInstSelector.cpp 
  _API_WrongModeInstSelector.cpp
  _API_WrongAPIInstSelector.cpp
  _API_BufferOverflowInstSelector.cpp
  _API_BufferUnderflowInstSelector.cpp
  _API_InappropriateCloseInstSelector.cpp


  _IO_WrongRetrievedAddressInstSelector.cpp
  _IO_WrongSavedAddressInstSelector.cpp
  _IO_WrongRetrievedFormatInstSelector.cpp
  _IO_WrongSavedFormatInstSelector.cpp

  
  _Res_MemoryExhaustionInstSelector.cpp
  _Res_DeadLockInstSelector.cpp
  _Res_InvalidPointerInstSelector.cpp
  _Res_LowMemoryInstSelector.cpp
  _Res_CPUHOGInstSelector.cpp
  _Res_MemoryLeakInstSelector.cpp
  _Res_ThreadKillerInstSelector.cpp
  _Res_StalePointerInstSelector.cpp
  _Res_UnderAccumulatorInstSelector.cpp

 
  _Data_BufferOverflow1InstSelector.cpp
  _Data_BufferOverflow2InstSelector.cpp
  _Data_WrongPointerInstSelector.cpp
  _Data_WrongSourceInstSelector.cpp
  _Data_WrongDestinationInstSelector.cpp
  _Data_No_OutputInstSelector.cpp
  _Data_Incorrect_OutputInstSelector.cpp
  

  _MPI_NoMessageInstSelector.cpp
  _MPI_InvalidMessageInstSelector.cpp
  _MPI_NoAckInstSelector.cpp
  _MPI_DeadLockInstSelector.cpp
  _MPI_InvalidSenderInstSelector.cpp
  _MPI_BufferOverflowInstSelector.cpp

  _Timing_RaceConditionInstSelector.cpp
  _Timing_HighFrequentEventInstSelector.cpp 
  _AutoRegSelector.cpp
  
)
