#ifndef LLFI_UTILS_H
#define LLFI_UTILS_H
#include "llvm/Function.h"
#include "llvm/Instruction.h"
#include "llvm/Value.h"

#include <map>
#include <string>

using namespace llvm;
namespace llfi {
std::string intToString(int i);

// return the terminate instruction of the function
Instruction *getTermInstofFunction(Function *func);
// return instumentation code insertion point for fi in reg of inst
Instruction *getInsertPtrforRegsofInst(Value *reg, Instruction *inst);

// get or set the LLFI index of the specified instruction. use metadata
long getLLFIIndexofInst(Instruction *inst);
void setLLFIIndexofInst(Instruction *inst);

// get the map of opcode name and their opcode
void genFullNameOpcodeMap(std::map<std::string, unsigned> &opcodenamemap);
}

#endif
