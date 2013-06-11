#ifndef LLFI_UTILS_H
#define LLFI_UTILS_H
#include "llvm/Function.h"
#include "llvm/Instruction.h"
#include "llvm/Value.h"

#include <map>
#include <string>

using namespace llvm;
namespace llfi {
Instruction *getTermInstofFunction(Function *func); 
Instruction *getInsertPtrforRegsofInst(Value *reg, Instruction *inst);

std::string intToString(int i);

bool is_injectFaultFuncCall(Instruction *I);

long getLLFIIndexofInst(Instruction *inst);
void setLLFIIndexofInst(Instruction *inst);

void genFullNameOpcodeMap(std::map<std::string, unsigned> &opcodenamemap);
}

#endif
