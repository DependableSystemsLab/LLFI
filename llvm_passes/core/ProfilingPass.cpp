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
//BEHROOZ-JUNE 3rd
#include "llvm/Support/CommandLine.h"


#include <list>
#include <map>
#include <vector>

#include "ProfilingPass.h"
#include "Controller.h"
#include "Utils.h"

using namespace llvm;

namespace llfi {

//BEHROOZ: JUNE 3rd
extern cl::opt< std::string > llfilogfile;

bool ProfilingPass::runOnModule(Module &M) {
	LLVMContext &context = M.getContext();

  std::map<Instruction*, std::list< int >* > *fi_inst_regs_map;
  Controller *ctrl = Controller::getInstance(M);
  ctrl->getFIInstRegsMap(&fi_inst_regs_map);
  //BEHROOZ: JUUNE 3rd
  std::string err;
  raw_fd_ostream logFile(llfilogfile.c_str(), err, sys::fs::F_Append);
  //BEHROOZ - END

  for (std::map<Instruction*, std::list< int >* >::const_iterator 
       inst_reg_it = fi_inst_regs_map->begin(); 
       inst_reg_it != fi_inst_regs_map->end(); ++inst_reg_it) {
    Instruction *fi_inst = inst_reg_it->first;
    std::list<int > *fi_regs = inst_reg_it->second;
    //BEHROOZ-MAY27: This section makes sure that we do not instrument the intrinsic functions 
    if(isa<CallInst>(fi_inst)){
      bool continue_flag=false;
      for (std::list<int>::iterator reg_pos_it_mem = fi_regs->begin();
        (reg_pos_it_mem != fi_regs->end()) && (*reg_pos_it_mem != DST_REG_POS); ++reg_pos_it_mem) {
        std::string reg_mem = fi_inst->getOperand(*reg_pos_it_mem)->getName();
        if ((reg_mem.find("memcpy") != std::string::npos) || (reg_mem.find("memset") != std::string::npos) || (reg_mem.find("expect") != std::string::npos) || (reg_mem.find("memmove") != std::string::npos)){
          logFile << "LLFI cannot instrument " << reg_mem << " intrinsic function"<< "\n";
          continue_flag=true;
          break;
        }
      }
      if(continue_flag)
        continue;
    }
    //BEHROOZ-MAY27: This is to make sure we do not instrument landingpad instructions.
    std::string current_opcode = fi_inst->getOpcodeName();
    if(current_opcode.find("landingpad") != std::string::npos){
      logFile << "LLFI cannot instrument " << current_opcode << " instruction" << "\n";
      continue;
    }
    //BEHROOZ-END


    Value *fi_reg = *(fi_regs->begin())==DST_REG_POS ? fi_inst : (fi_inst->getOperand(*(fi_regs->begin())));
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

  //BEHROOZ-JUNE 3rd
  logFile.close();

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
