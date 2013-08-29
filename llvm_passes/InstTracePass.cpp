/***************
InstTrace.cpp
Author: Sam Coulter
  This llvm pass is part of the greater LLFI framework
  
  Run the pass with the opt -InstTrace option after loading LLFI.so
  
  This pass injects a function call before every non-void-returning, 
  non-phi-node instruction that prints trace information about the executed
  instruction to a file specified during the pass.
***************/

#include <vector>
#include <cmath>

#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Target/TargetData.h"

#include "Utils.h"

using namespace llvm;

cl::opt<bool> debugtrace( "debugtrace",
              cl::desc("Output Trace insertion information"),
              cl::init(false));
cl::opt<int> maxtrace( "maxtrace",
            cl::desc("Maximum number of instructions that will be traced after fault"),
            cl::init(1000));

namespace llfi {

struct InstTrace : public FunctionPass {

  static char ID;
  Function::iterator lastBlock;
  BasicBlock::iterator lastInst;
  
  InstTrace() : FunctionPass(ID) {}
  
  //Add AnalysisUsage Pass as prerequisite for InstTrace Pass
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequired<TargetData>();
  }
  
  virtual bool doInitialization(Module &M) {
    return false;
  }
  
  virtual bool doFinalization(Module &M) {
    //Dont forget to delete the output filename string!
    Function* mainfunc = M.getFunction("main");
    if (mainfunc == NULL) {
      errs() << "ERROR: Function main does not exist, " <<
          "which is required by LLFI\n";
      exit(1);
    }

    LLVMContext &context = M.getContext();
    FunctionType *postinjectfunctype = FunctionType::get(
        Type::getVoidTy(context), false); 
    Constant *postracingfunc = M.getOrInsertFunction("postTracing",
                                             postinjectfunctype);

    BasicBlock *exitblock = &mainfunc->back();
    CallInst::Create(postracingfunc, "", exitblock->getTerminator());

    return true;
  }
  
  long fetchLLFIInstructionID(Instruction *targetInst) {
    return llfi::getLLFIIndexofInst(targetInst);
  }

  virtual bool runOnFunction(Function &F) {
    //Create handles to the functions parent module and context
    LLVMContext& context = F.getContext();
    Module *M = F.getParent();
  
    //iterate through each basicblock of the function
    for (inst_iterator instIterator = inst_begin(F), lastInst = inst_end(F);
         instIterator != lastInst; ++instIterator) {
  
        //Print some Debug Info as the pass is being run
      Instruction *inst = &*instIterator;
  
      if (debugtrace) {
        errs() << llfi::isLLFIIndexedInst(inst) << " InstTrace: Found Instruction\n";
        if (!llfi::isLLFIIndexedInst(inst)) {
          errs() << "   Instruction was not indexed\n";
        } else {
          errs() << "   Opcode Name: " << inst->getOpcodeName() << "\n"
                  << "   Opcode: " << inst->getOpcode() << "\n"
                 << "   Parent Function Name: " << F.getNameStr() << "\n";
        }
      }
      if (llfi::isLLFIIndexedInst(inst)) {
  
        //Find instrumentation point for current instruction
	Instruction *insertPoint;
	if (!inst->isTerminator()) {
		insertPoint = llfi::getInsertPtrforRegsofInst(inst, inst);
	} 
	else {
		insertPoint = inst;
	}
  AllocaInst* ptrInst;
  if (inst->getType() != Type::getVoidTy(context)) {
    //insert an instruction Allocate stack memory to store/pass instruction value
    ptrInst = new AllocaInst(inst->getType(), "", insertPoint);
    //Insert an instruction to Store the instruction Value!
    new StoreInst(inst, ptrInst, insertPoint);
	}
	else {
		ptrInst = new AllocaInst(Type::getInt32Ty(context), "", insertPoint);
		new StoreInst(ConstantInt::get(IntegerType::get(context,32), 0), 
		ptrInst, insertPoint);
	}
        
        //Insert instructions to allocate stack memory for opcode name
        llvm::Value* OPCodeName = llvm::ConstantArray::get(context, inst->getOpcodeName());
        AllocaInst* OPCodePtr = new AllocaInst(OPCodeName->getType(), "", insertPoint);
        new StoreInst(OPCodeName, OPCodePtr, insertPoint);
  
        //Create the decleration of the printInstTracer Function
        std::vector<const Type*> parameterVector(5);
        parameterVector[0] = Type::getInt32Ty(context); //ID
        parameterVector[1] = OPCodePtr->getType();     //Ptr to OpCode
        parameterVector[2] = Type::getInt32Ty(context); //Size of Inst Value
        parameterVector[3] = ptrInst->getType();    //Ptr to Inst Value
        parameterVector[4] = Type::getInt32Ty(context); //Int of max traces
        
        FunctionType* traceFuncType = FunctionType::get(Type::getVoidTy(context), 
                                                        parameterVector, false);
        Constant *traceFunc = M->getOrInsertFunction("printInstTracer", traceFuncType); 
  
        //Insert the tracing function, passing it the proper arguments
        std::vector<Value*> traceArgs;
        //Fetch the LLFI Instruction ID:
        ConstantInt* IDConstInt = ConstantInt::get(IntegerType::get(context, 32), 
                                                   fetchLLFIInstructionID(inst));
        
        //Fetch size of instruction value        
        TargetData &td = getAnalysis<TargetData>();
        //The size must be rounded up before conversion to bytes because some data in llvm
        //can be like 6 bits if it only needs 6 bits out of an 8bit/1byte data type
        float bitSize;
        if (inst->getType() != Type::getVoidTy(context)) {
          bitSize = (float)td.getTypeSizeInBits(inst->getType());
        }
        else {
          bitSize = 8;
        }
        int byteSize = (int)ceil(bitSize / 8.0);
        ConstantInt* instValSize = ConstantInt::get(
                                      IntegerType::get(context, 32), byteSize);
        
        //Fetch maxtrace number:
        ConstantInt* maxTraceConstInt =
            ConstantInt::get(IntegerType::get(context, 32), maxtrace);
        
        //Load All Arguments
        traceArgs.push_back(IDConstInt);
        traceArgs.push_back(OPCodePtr);
        traceArgs.push_back(instValSize);
        traceArgs.push_back(ptrInst);
        traceArgs.push_back(maxTraceConstInt);
  
        //Create the Function
        CallInst::Create(traceFunc, traceArgs.begin(),traceArgs.end(), "", insertPoint);
      }
    }//Function Iteration
  
    return true; //Tell LLVM that the Function was modified
  }//RunOnFunction
};//struct InstTrace

//Register the pass with the llvm
char InstTrace::ID = 0;
static RegisterPass<InstTrace> X("insttracepass", 
    "Add tracing function calls in program to trace instruction value at runtime", 
    false, false);

}//namespace llfi

