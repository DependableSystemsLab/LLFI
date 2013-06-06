//This pass is run after the transform pass for inserting hooks for fault injection 
#ifndef PROFILING_H
#define PROFILING_H

// TODO: move unnessary headers to cpp file
#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/InstVisitor.h"
#include "llvm/Support/Debug.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/Dominators.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/CommandLine.h"


#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <string>


using namespace llvm;


namespace llfi {
class ProfilingPass: public ModulePass {
 public:
  ProfilingPass() : ModulePass(ID) {}
	virtual bool runOnModule(Module &M);
	static char ID;

 private: //doFinalization is not a member of modulepass in llvm 2.9
  bool doFinalization(Module &M);
 private:
  Constant *getLLFILibProfilingFunc(Module &M);
  Constant *getLLFILibEndProfilingFunc(Module &M);
};

char ProfilingPass::ID=0;
}

#endif
