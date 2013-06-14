//This pass is run after the transform pass for inserting hooks for fault injection 
#ifndef PROFILING_PASS_H
#define PROFILING_PASS_H

#include "llvm/Constants.h"
#include "llvm/Pass.h"
#include "llvm/Module.h"

#include <iostream>

using namespace llvm;
namespace llfi {
class ProfilingPass: public ModulePass {
 public:
  ProfilingPass() : ModulePass(ID) {}
	virtual bool runOnModule(Module &M);
	static char ID;

 private: 
  void addEndProfilingFuncCall(Module &M);
 private:
  Constant *getLLFILibProfilingFunc(Module &M);
  Constant *getLLFILibEndProfilingFunc(Module &M);
};

char ProfilingPass::ID=0;
}

#endif
