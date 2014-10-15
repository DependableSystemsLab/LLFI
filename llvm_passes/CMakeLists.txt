include(../config/llvm_passes.cmake)


add_llvm_loadable_module(llfi-passes
  FaultInjectionPass.cpp
  InstTracePass.cpp
  LLFIDotGraphPass.cpp
  Utils.cpp
  Controller.cpp
  FICustomSelectorManager.cpp
  FIInstSelector.cpp
  FIInstSelectorManager.cpp
  FIRegSelector.cpp
  FuncNameFIInstSelector.cpp
  GenLLFIIndexPass.cpp
  ProfilingPass.cpp
  InstTypeFIInstSelector.cpp
  RegLocBasedFIRegSelector.cpp
  SampleFIInstSelector.cpp
  SampleFIRegSelector.cpp
  LLFIIndexFIInstSelector.cpp
  AutoScan_Pass.cpp

    
    
  _API_NoOpenSelector.cpp
  _API_NoCloseSelector.cpp
  _API_Incorrect_OutputSelector.cpp
  _API_No_OutputSelector.cpp 
  _API_WrongModeSelector.cpp
  _API_WrongAPISelector.cpp
  _API_BufferOverflowSelector.cpp
  _API_BufferUnderflowSelector.cpp
  _API_InappropriateCloseSelector.cpp


  _IO_WrongRetrievedAddressSelector.cpp
  _IO_WrongSavedAddressSelector.cpp
  _IO_WrongRetrievedFormatSelector.cpp
  _IO_WrongSavedFormatSelector.cpp

  
  _Res_MemoryExhaustionSelector.cpp
  _Res_DeadLockSelector.cpp
  _Res_InvalidPointerSelector.cpp
  _Res_LowMemorySelector.cpp
  _Res_CPUHOGSelector.cpp
  _Res_MemoryLeakSelector.cpp
  _Res_ThreadKillerSelector.cpp
  _Res_StalePointerSelector.cpp
  _Res_UnderAccumulatorSelector.cpp

 
  _Data_BufferOverflowMallocSelector.cpp
  _Data_BufferOverflowMemmoveSelector.cpp
  _Data_WrongPointerSelector.cpp
  _Data_WrongSourceSelector.cpp
  _Data_WrongDestinationSelector.cpp
  _Data_No_OutputSelector.cpp
  _Data_Incorrect_OutputSelector.cpp
  _Data_CorruptionSelector.cpp

  _MPI_NoMessageSelector.cpp
  _MPI_InvalidMessageSelector.cpp
  _MPI_NoAckSelector.cpp
  _MPI_NoDrainSelector.cpp 
  _MPI_DeadLockSelector.cpp
  _MPI_InvalidSenderSelector.cpp
  _MPI_PacketStormSelector.cpp

  _Timing_RaceConditionSelector.cpp
  _Timing_HighFrequentEventSelector.cpp 
  _SoftwareFaultRegSelectors.cpp
  
  
)
