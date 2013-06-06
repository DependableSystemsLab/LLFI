//===- faultinjection.cpp - Fault Injection Pass -==//
//
//                     LLFI Distribution
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This pass instruments selected registers of instruction with calls to fault
// injection libraries
//
// The fault injection function is a C function which performs the fault
// injection at runtime
// See fi_random.c injectFunc() function for more details on the fault injection 
// function. This function definition is linked to the instrumented 
// bitcode file (after this pass). 
//
//
//===----------------------------------------------------------------------===//

#include "faultinjectionpass.h"
#include "controller.h"
#include "utils.h"

namespace llfi{

std::string FaultInjection::getFIFuncNameforType(const Type *type) {
  std::string funcname;
  if (fi_rettype_funcname_map.find(type) != 
      fi_rettype_funcname_map.end()) {
    funcname = fi_rettype_funcname_map[type];
  } else {
    funcname = "injectFault";
    int ficount = fi_rettype_funcname_map.size();	
    funcname += intToString(ficount);
    fi_rettype_funcname_map[type] = funcname;
  }
  return funcname;
}

void FaultInjection::insertInjectionFuncCall(
    std::map<Instruction*, std::list< Value* >* > *inst_regs_map, Module &M) {

  for (std::map<Instruction*, std::list< Value* >* >::iterator inst_reg_it =
       inst_regs_map->begin(); inst_reg_it != inst_regs_map->end(); 
       ++inst_reg_it) {
    Instruction *fi_inst = inst_reg_it->first;
    std::list<Value* > *fi_regs = inst_reg_it->second;
    for (std::list<Value* >::iterator reg_it = fi_regs->begin(); 
         reg_it != fi_regs->end(); ++reg_it) {
      Value *fi_reg = *reg_it;
      const Type* returntype = fi_reg->getType();
      
      // function declaration
      LLVMContext& context = M.getContext();
      std::vector<const Type*> paramtypes(2);
      paramtypes[0] = Type::getInt32Ty(context);	// Fault index
      paramtypes[1] = returntype;	// type of the fault injection function
      FunctionType* injectfunctype = FunctionType::get(returntype, 
                                                       paramtypes, false);
      std::string funcname = getFIFuncNameforType(returntype);
      Constant *injectfunc = M.getOrInsertFunction(funcname, injectfunctype);

      // argument preparation for calling function
      const Type *itype = paramtypes[0];
      // since the source register is another way of simulating fault
      // injection into the instruction, use its index instead
      Value *indexval = ConstantInt::get(itype, getFIIndexofReg(fi_inst));
      std::vector<Value*> args(2);
      args[0] = indexval;
      args[1] = fi_reg;
      Instruction *insertptr = NULL;
      insertptr = getInsertPtrforRegsofInst(fi_reg, fi_inst);
      std::string ficallname = "fi";
      Instruction* ficall = CallInst::Create(
          injectfunc, args.begin(), args.end(), ficallname, insertptr);

      // redirect the data dependencies
      if (fi_reg == fi_inst) {
        // inject into destination
        fi_inst->replaceAllUsesWith(ficall);
        ficall->replaceUsesOfWith(ficall, fi_inst);
      } else {
        // inject into source
        fi_inst->replaceUsesOfWith(fi_reg, ficall);
      }
    }
  }
}

void FaultInjection::createInjectionFuncforType(
    Module &M, const Type *fitype, std::string &fi_name, Constant* injectfunc, 
    Constant *pre_fi_func) {
  // TODO: split the prefunc and injectFunc to different funcs

  DEBUG(errs() << "Creating fault injection function: " << fi_name << "\n");
  LLVMContext &context = M.getContext();
  Function *f = M.getFunction(fi_name);
  std::vector<Value*> args;
  for(Function::arg_iterator ai = f->arg_begin(), ae = f->arg_end(); 
      ai != ae; ++ai)
    args.push_back(&*ai);
  // args[0] fault index, args[1] fault injection instruction

  // Insert call to prefix function
  BasicBlock* entryblock = BasicBlock::Create(context, "entry", f);
	
  // store the value of target instruction to memory
  const Type *fi_inst_type = args[1]->getType();
  AllocaInst *tmploc = new AllocaInst(fi_inst_type, "tmploc", entryblock);
  new StoreInst(args[1], tmploc, entryblock);

  std::vector<Value*> pre_fi_args(2);
  pre_fi_args[0] = args[0]; //FI Number
	
  TargetData& td = getAnalysis<TargetData>();
  int size = td.getTypeSizeInBits(fi_inst_type);
  pre_fi_args[1] = ConstantInt::get(Type::getInt32Ty(context), size); 
  Value *prefuncval = CallInst::Create(pre_fi_func, pre_fi_args.begin(),
                              pre_fi_args.end(), "llfi_pre_cond", entryblock);

  BasicBlock *fi_block = BasicBlock::Create(context, "inject", f);	
  BasicBlock *exitblock = BasicBlock::Create(context,"exit", f );
  //if prefuncval is true, goto inject function
  BranchInst::Create(fi_block, exitblock, prefuncval, entryblock);		
  BranchInst *fi2exit_branch = BranchInst::Create(exitblock, fi_block);


  std::vector<Value*> fi_args(3);
  fi_args[0] = args[0]; //FINumber
  fi_args[1] = pre_fi_args[1]; // The size
  fi_args[2] = new BitCastInst(tmploc, 
                    PointerType::get(Type::getInt8Ty(context), 0),
                    "tmploc_cast", fi2exit_branch);
  CallInst::Create(injectfunc, fi_args.begin(), fi_args.end(), "",
                   fi2exit_branch);

  LoadInst *updateval = new LoadInst(tmploc, "updateval", exitblock);
  ReturnInst::Create(context, updateval, exitblock);
}

void FaultInjection::createInjectionFunctions(Module &M) {
  Constant *pre_fi_func = getLLFILibPreFIFunc(M);
  Constant *injectfunc = getLLFILibFIFunc(M);
  
  for (std::map<const Type*, std::string>::iterator fi = 
       fi_rettype_funcname_map.begin(),
       fe = fi_rettype_funcname_map.end(); fi != fe; ++fi) {
    const Type *fi_type = fi->first;
    std::string fi_name = fi->second;
    createInjectionFuncforType(M, fi_type, fi_name, injectfunc, pre_fi_func);
  }
}

bool FaultInjection::runOnModule(Module &M) {
  doInitialization(M);

  std::map<Instruction*, std::list< Value* >* > *fi_inst_regs_map;
  Controller *ctrl = Controller::getInstance(M);
  ctrl->getFIInstRegsMap(&fi_inst_regs_map);
  
  insertInjectionFuncCall(fi_inst_regs_map, M);


  doFinalization(M);
  return true;
}

bool FaultInjection::doInitialization(Module &M) {
  Function* mainfunc = M.getFunction("main");
  if (mainfunc == NULL) {
    // TODO: logging information other that standard output
    // TODO: see if we can return non-zero value to terminate the pass
    errs() << "Function main does not exist, which is required by LLFI\n";
    exit(1);
  }

  return false;
}

bool FaultInjection::doFinalization(Module &M) {
  Function *mainfunc = M.getFunction("main");
  BasicBlock *entryblock = &mainfunc->front();

  // function call for initInjections
  Constant *initfunc = getLLFILibInitInjectionFunc(M);
  CallInst::Create(initfunc, "", entryblock->getFirstNonPHI());
  
  // function call for postInjections
  BasicBlock *exitblock = &mainfunc->back();
  Constant *postfifunc = getLLFILibPostInjectionFunc(M);
  CallInst::Create(postfifunc, "", exitblock->getTerminator());

	createInjectionFunctions(M);
  return true;
}

Constant *FaultInjection::getLLFILibPreFIFunc(Module &M) {
  std::vector<const Type*> pre_fi_func_param_types(2); 
  LLVMContext& context = M.getContext();
  pre_fi_func_param_types[0] = Type::getInt32Ty(context);
  pre_fi_func_param_types[1] = Type::getInt32Ty(context);
  FunctionType *pre_fi_func_type = FunctionType::get(Type::getInt1Ty(context),
                                                pre_fi_func_param_types, false);
  Constant *pre_fi_func = M.getOrInsertFunction("preFunc", pre_fi_func_type);
  return pre_fi_func;
}

Constant *FaultInjection::getLLFILibFIFunc(Module &M) {
  LLVMContext& context = M.getContext();
  std::vector<const Type*> fi_func_param_types(3);
  fi_func_param_types[0] = Type::getInt32Ty(context); 
  fi_func_param_types[1] = Type::getInt32Ty(context); 
  fi_func_param_types[2] = PointerType::get(Type::getInt8Ty(context), 0);
  FunctionType *injectfunctype = FunctionType::get(Type::getVoidTy(context),
                                                   fi_func_param_types, false);
  Constant *injectfunc = M.getOrInsertFunction("injectFunc", injectfunctype);
  return injectfunc;
} 

Constant *FaultInjection::getLLFILibInitInjectionFunc(Module &M) {
  LLVMContext &context = M.getContext();
  FunctionType *fi_init_func_type = 
      FunctionType::get(Type::getVoidTy(context), false); 
  Constant *initfunc = M.getOrInsertFunction("initInjections",
                                              fi_init_func_type);
  return initfunc;
}

Constant *FaultInjection::getLLFILibPostInjectionFunc(Module &M) {
  LLVMContext &context = M.getContext();
  FunctionType *postinjectfunctype = FunctionType::get(
      Type::getVoidTy(context), false); 
  Constant *postfifunc = M.getOrInsertFunction("postInjections",
                                             postinjectfunctype);
  return postfifunc;
}

static RegisterPass<FaultInjection> X("faultinjectionpass", "FaultInjection Pass",
                                      false, false);
}
