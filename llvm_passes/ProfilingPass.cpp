//===- profilingpass.cpp - Dynamic Instruction Profiling Pass -==//
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

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

#include <list>
#include <map>
#include <vector>

#include "ProfilingPass.h"
#include "Controller.h"
#include "Utils.h"

using namespace llvm;

namespace llfi {

bool ProfilingPass::runOnModule(Module &M) {
	LLVMContext &context = M.getContext();

  std::map<Instruction*, std::list< Value* >* > *fi_inst_regs_map;
  Controller *ctrl = Controller::getInstance(M);
  ctrl->getFIInstRegsMap(&fi_inst_regs_map);

  for (std::map<Instruction*, std::list< Value* >* >::const_iterator 
       inst_reg_it = fi_inst_regs_map->begin(); 
       inst_reg_it != fi_inst_regs_map->end(); ++inst_reg_it) {
    Instruction *fi_inst = inst_reg_it->first;
    std::list<Value* > *fi_regs = inst_reg_it->second;
    Value *fi_reg = *(fi_regs->begin());
    Instruction *insertptr = getInsertPtrforRegsofInst(fi_reg, fi_inst);
    
    // function declaration
    Constant* profilingfunc = getLLFILibProfilingFunc(M);

    // prepare for the calling argument and call the profiling function
    std::vector<Value*> profilingarg(1);
    const IntegerType* itype = IntegerType::get(context, 32);

    //LLVM 3.3 Upgrading
    IntegerType* itype_non_const = const_cast<IntegerType*>(itype);
    Value* opcode = ConstantInt::get(itype_non_const, fi_inst->getOpcode());
    profilingarg[0] = opcode; 
    ArrayRef<Value*> profilingarg_array_ref(profilingarg);

    CallInst::Create(profilingfunc, profilingarg_array_ref,
                     "", insertptr);
  }

  addEndProfilingFuncCall(M);
  return true;
}


void ProfilingPass::addEndProfilingFuncCall(Module &M) {
  Function* mainfunc = M.getFunction("main");
  if (mainfunc != NULL) {
    Constant *endprofilefunc = getLLFILibEndProfilingFunc(M);

    // function call
    std::set<Instruction*> exitinsts;
    getProgramExitInsts(M, exitinsts);
    assert (exitinsts.size() != 0 
            && "Program does not have explicit exit point");

    for (std::set<Instruction*>::iterator it = exitinsts.begin();
         it != exitinsts.end(); ++it) {
      Instruction *term = *it;
      CallInst::Create(endprofilefunc, "", term);
    }
  } else {
    errs() << "ERROR: Function main does not exist, " << 
        "which is required by LLFI\n";
    exit(1);
  }
}

Constant *ProfilingPass::getLLFILibProfilingFunc(Module &M) {
	LLVMContext& context = M.getContext();
  std::vector<Type*> paramtypes(1);
  paramtypes[0] = Type::getInt32Ty(context);

  // LLVM 3.3 Upgrading
  ArrayRef<Type*> paramtypes_array_ref(paramtypes);

  FunctionType* profilingfunctype = FunctionType::get(
      Type::getVoidTy(context), paramtypes_array_ref, false);
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
                                     "Profiling pass", false, false);
}
