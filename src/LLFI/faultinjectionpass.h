#ifndef FAULTINJECTION_PASS_H
#define FAULTINJECTION_PASS_H

#include "llvm/Constants.h"
#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"

#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace llvm;

namespace llfi {
class FaultInjectionPass: public ModulePass {
 public:
  FaultInjectionPass() : ModulePass(ID) { }
  virtual bool runOnModule(Module &M);	
  static char ID;
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequired<TargetData>();
  }

 private: 
  void checkforMainFunc(Module &M);
  void finalize(Module& M);

  void insertInjectionFuncCall(
      std::map<Instruction*, std::list< Value* >* > *inst_regs_map, Module &M);
  void createInjectionFuncforType(Module &M, const Type *functype, 
                                  std::string &funcname, Constant *fi_func, 
                                  Constant *pre_func);
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
