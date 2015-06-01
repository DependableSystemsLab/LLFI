include(../config/llvm_passes.cmake)

set(LLVM_PASSES_DIRS_LLFI hardware_failures core software_failures)

include_directories(${LLVM_PASSES_DIRS_LLFI})


add_llvm_loadable_module(llfi-passes
  SampleFIInstSelector.cpp
  SampleFIRegSelector.cpp
  SoftwareFailureAutoScanPass.cpp
  HardwareFailureAutoScanPass.cpp

  core/FaultInjectionPass.cpp
  core/InstTracePass.cpp
  core/LLFIDotGraphPass.cpp
  core/Utils.cpp
  core/Controller.cpp
  core/FICustomSelectorManager.cpp
  core/FIInstSelector.cpp
  core/FIInstSelectorManager.cpp
  core/FIRegSelector.cpp
  core/GenLLFIIndexPass.cpp
  core/ProfilingPass.cpp
  core/RegLocBasedFIRegSelector.cpp

  hardware_failures/FuncNameFIInstSelector.cpp
  hardware_failures/LLFIIndexFIInstSelector.cpp
  hardware_failures/InstTypeFIInstSelector.cpp
  
    
  software_failures/_API_NoOpenSelector.cpp
  software_failures/_API_NoCloseSelector.cpp
  software_failures/_API_Incorrect_OutputSelector.cpp
  software_failures/_API_No_OutputSelector.cpp 
  software_failures/_API_WrongModeSelector.cpp
  software_failures/_API_WrongAPISelector.cpp
  software_failures/_API_BufferOverflowSelector.cpp
  software_failures/_API_BufferUnderflowSelector.cpp
  software_failures/_API_InappropriateCloseSelector.cpp


  software_failures/_IO_WrongRetrievedAddressSelector.cpp
  software_failures/_IO_WrongSavedAddressSelector.cpp
  software_failures/_IO_WrongRetrievedFormatSelector.cpp
  software_failures/_IO_WrongSavedFormatSelector.cpp

  
  software_failures/_Res_MemoryExhaustionSelector.cpp
  software_failures/_Res_DeadLockSelector.cpp
  software_failures/_Res_InvalidPointerSelector.cpp
  software_failures/_Res_LowMemorySelector.cpp
  software_failures/_Res_CPUHOGSelector.cpp
  software_failures/_Res_MemoryLeakSelector.cpp
  software_failures/_Res_ThreadKillerSelector.cpp
  software_failures/_Res_StalePointerSelector.cpp
  software_failures/_Res_UnderAccumulatorSelector.cpp

 
  software_failures/_Data_BufferOverflowMallocSelector.cpp
  software_failures/_Data_BufferOverflowMemmoveSelector.cpp
  software_failures/_Data_WrongPointerSelector.cpp
  software_failures/_Data_WrongSourceSelector.cpp
  software_failures/_Data_WrongDestinationSelector.cpp
  software_failures/_Data_No_OutputSelector.cpp
  software_failures/_Data_Incorrect_OutputSelector.cpp
  software_failures/_Data_CorruptionSelector.cpp

  software_failures/_MPI_NoMessageSelector.cpp
  software_failures/_MPI_InvalidMessageSelector.cpp
  software_failures/_MPI_NoAckSelector.cpp
  software_failures/_MPI_NoDrainSelector.cpp 
  software_failures/_MPI_DeadLockSelector.cpp
  software_failures/_MPI_InvalidSenderSelector.cpp
  software_failures/_MPI_PacketStormSelector.cpp

  software_failures/_Timing_RaceConditionSelector.cpp
  software_failures/_Timing_HighFrequentEventSelector.cpp 
  software_failures/_SoftwareFaultRegSelectors.cpp
  
  
)
