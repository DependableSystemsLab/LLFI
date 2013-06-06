#ifndef LLFI_UTILS_H
#define LLFI_UTILS_H

#include "llvm/Function.h"
#include "llvm/Instruction.h"
#include "llvm/Value.h"

using namespace llvm;

namespace llfi {
Instruction *getTermInstofFunction(Function *func); 
Instruction *getInsertPtrforRegsofInst(Value *reg, Instruction *inst);

std::string intToString(int i);

bool is_injectFaultFuncCall(Instruction *I);

long getFIIndexofReg(Value *reg);
}

#endif
