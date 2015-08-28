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
  
  software_failures/_Timing_HighFrequentEventSelector.cpp 
  software_failures/_SoftwareFaultRegSelectors.cpp
  
  #FIDL - DO NOT MODIFY UNTIL '#END'
  #END
  
)
