#ifndef FAULTINJECTION_PASS_H
#define FAULTINJECTION_PASS_H

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
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AliasSetTracker.h"
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Support/CommandLine.h"

// STL includes
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <string>
#include <utility>


using namespace llvm;

namespace llfi {
class FaultInjectionPass: public ModulePass {
 public:
  FaultInjectionPass() : ModulePass(ID) { }
  virtual bool runOnModule(Module &M);	
  static char ID;
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequired<TargetData>();
    //AU.addRequired<DominatorTree>();
    //AU.addRequired<AliasAnalysis>();
  }

 private: // the doInitialization and doFinalization are not in ModulePass
  bool doInitialization(Module &M);
  bool doFinalization(Module& M);
 private:
  void insertInjectionFuncCall(
      std::map<Instruction*, std::list< Value* >* > *inst_regs_map, Module &M);
  void createInjectionFuncforType(Module &M, const Type* functype, 
                                  std::string &funcname, Constant* fi_func, 
                                  Constant* pre_func);
	void createInjectionFunctions(Module &M);

 private:
  std::string getFIFuncNameforType(const Type* type);
  
  Constant *getLLFILibPreFIFunc(Module &M);
  Constant *getLLFILibFIFunc(Module &M);
  Constant *getLLFILibInitInjectionFunc(Module &M);
  Constant *getLLFILibPostInjectionFunc(Module &M);
 private:
  std::map<const Type*, std::string> fi_rettype_funcname_map;
};

char FaultInjectionPass::ID=0;
}
#endif
