//===- profiling.cpp - Dynamic Instruction Profiling Pass -==//
//
//                     LLFI Distribution
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// The trace function is a C function which increments the count 
// when the function is executed
// See profiling_lib.c doProfiling() function for more details. This function 
// definition is linked to the instrumented bitcode file (after this pass). 
//===----------------------------------------------------------------------===//


#include "profilingpass.h"
#include "controller.h"
#include "utils.h"

using namespace llvm;

namespace llfi {

bool ProfilingPass::runOnModule(Module &M) {
	LLVMContext &context = M.getContext();

  std::map<Instruction*, std::list< Value* >* > *fi_inst_regs_map;
  llfi::Controller ctrl;
  ctrl.init(&M);
  ctrl.getFIInstRegsMap(&fi_inst_regs_map);

  for (std::map<Instruction*, std::list< Value* >* >::iterator inst_reg_it =
       fi_inst_regs_map->begin(); inst_reg_it != fi_inst_regs_map->end(); 
       ++inst_reg_it) {
    Instruction *fi_inst = inst_reg_it->first;
    std::list<Value* > *fi_regs = inst_reg_it->second;
    for (std::list<Value* >::iterator reg_it = fi_regs->begin(); 
         reg_it != fi_regs->end(); ++reg_it) {
      Value *fi_reg = *reg_it;
      Instruction *insertptr = getInsertPtrforRegsofInst(fi_reg, fi_inst);
      
      // function declaration
      Constant* profilingfunc = getLLFILibProfilingFunc(M);

      // prepare for the calling argument and call the profiling function
      std::vector<Value*> profilingarg(1);
      const IntegerType* itype = IntegerType::get(context, 32);
      Value* opcode = ConstantInt::get(itype, fi_inst->getOpcode());
      profilingarg[0] = opcode; 
      
      CallInst::Create(profilingfunc, profilingarg.begin(), profilingarg.end(),
                       "", insertptr);
    }
  }

  doFinalization(M);

  return true;
}


bool ProfilingPass::doFinalization(Module &M) {
  Function* mainfunc = M.getFunction("main");
  if (mainfunc != NULL) {
    Constant *endprofilefunc = getLLFILibEndProfilingFunc(M);

    // function call
    Instruction *term = getTermInstofFunction(mainfunc);
    CallInst::Create(endprofilefunc, "", term);
  } else {
    // TODO: logging information other that standard output
    // TODO: see if we can return non-zero value to terminate the pass
    errs() << "Function main does not exist, which is required by LLFI\n";
    exit(1);
  }

  // TODO: understand what the return value means and what's the impact
  return true; 
}

Constant *ProfilingPass::getLLFILibProfilingFunc(Module &M) {
	LLVMContext& context = M.getContext();
  std::vector<const Type*> paramtypes(1);
  paramtypes[0] = Type::getInt32Ty(context);
  FunctionType* profilingfunctype = FunctionType::get(
      Type::getVoidTy(context), paramtypes, false);
  Constant *profilingfunc = M.getOrInsertFunction(
      "doProfiling", profilingfunctype);
  return profilingfunc;
}

Constant *ProfilingPass::getLLFILibEndProfilingFunc(Module &M) {
  LLVMContext& context = M.getContext();
  FunctionType* endprofilingfunctype = FunctionType::get(
      Type::getVoidTy(context), false);
  Constant *endprofilefunc = M.getOrInsertFunction("endProfiling", 
                                                endprofilingfunctype);
  return endprofilefunc;
}

static RegisterPass<ProfilingPass> X("profilingpass", 
                                     "Profiling Pass", false, false);
}
