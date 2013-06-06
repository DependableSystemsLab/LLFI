#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "utils.h"

#include <sstream>
#include <string>

namespace llfi {
Instruction *getTermInstofFunction(Function *func) {
  BasicBlock &termbb = func->back();
  Instruction *ret = termbb.getTerminator();

  assert(isa<ReturnInst>(ret) && "Last instruction is not return instruction");
  return ret;
}

Instruction *getInsertPtrforRegsofInst(Value *reg, Instruction *inst) {
  // TODO: This insert points can be extended later
  // TODO: different checks needed for different versions of llvm
  if (reg == inst) {
    // inject into destination reg, insert after inst
    if (inst->isTerminator()) {
      // TODO: log the info to somewhere else
      errs() << "LLFI not able to inject into destination register of " <<
            *inst << ", change isRegofInstInjectable to fix it\n";
      exit(2);
    } else {
      BasicBlock::iterator bb_it = inst;
      // TODO: handle the case where inst is a phi node
      while (isa<PHINode>(++bb_it)) ;
      return bb_it;
    }
  } else {
    // Assume the reg is the src of inst, insert before inst
    if (isa<PHINode>(inst)) {
      errs() << "LLFI not able to inject into source register of " <<
          *inst << ", change isRegofInstInjectable to fix it\n";
      exit(2);
    }
    return inst;
  }
}


std::string intToString(int i) {
  std::stringstream s;
  s << i;
  return s.str();
}

bool is_injectFaultFuncCall(Instruction *I) {
  std::string injectfunc("injectFault");
  CallInst *ci = dyn_cast<CallInst>(I);
  if(!ci)
    return false;
  Function *F = ci->getCalledFunction();
  std::string funcname;
  if(F)
    funcname = F->getNameStr();
  else
    return false;
  if(funcname.find(injectfunc) != std::string::npos)
    return true;
  return false;
}

// TODO: use metadata to generate the index
static long long fi_index = 0;
long getFIIndexofReg(Value *reg) {
  return fi_index++;
}

void genFullNameOpcodeMap(
    std::map<std::string, unsigned> &opcodenamemap) {
#define HANDLE_INST(N, OPC, CLASS) \
  opcodenamemap[std::string(Instruction::getOpcodeName(N))] = N;
#include "llvm/Instruction.def"
}

}
