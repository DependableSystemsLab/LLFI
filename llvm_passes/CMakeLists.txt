include(../config/llvm_passes.cmake)


add_llvm_loadable_module(llfi-passes
  faultinjectionpass.cpp
  instTrace.cpp
  utils.cpp
  controller.cpp
  ficustomselectormanager.cpp
  fiinstselector.cpp
  firegselector.cpp
  genllfiindexpass.cpp
  profilingpass.cpp
  insttypefiinstselector.cpp
  reglocbasedfiregselector.cpp
  samplefiinstselector.cpp
  samplefiregselector.cpp
  LLFIIndexFIInstSelector.cpp
)
