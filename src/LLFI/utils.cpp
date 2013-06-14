#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/MetaData.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include <sstream>

#include "utils.h"

namespace llfi {

std::string intToString(int i) {
  std::stringstream s;
  s << i;
  return s.str();
}

Instruction *getTermInstofFunction(Function *func) {
  BasicBlock &termbb = func->back();
  Instruction *ret = termbb.getTerminator();

  assert(isa<ReturnInst>(ret) && "Last instruction is not return instruction");
  return ret;
}

Instruction *getInsertPtrforRegsofInst(Value *reg, Instruction *inst) {
  // TODO: This insert points can be extended later
  // TODO: different checks may be needed for different versions of llvm
  if (reg == inst) {
    // inject into destination reg, insert after inst
    if (inst->isTerminator()) {
      errs() << "ERROR: LLFI not able to inject into destination register of " 
          << *inst << ", change isRegofInstInjectable() to fix it\n";
      exit(2);
    } else {
      BasicBlock::iterator bb_it = inst;
      while (isa<PHINode>(++bb_it)) ;
      return bb_it;
    }
  } else {
    // Assume the reg is the src of inst, insert before inst
    if (isa<PHINode>(inst)) {
      errs() << "ERROR: LLFI not able to inject into source register of " <<
          *inst << ", change isRegofInstInjectable to fix it\n";
      exit(2);
    }
    return inst;
  }
}

long getLLFIIndexofInst(Instruction *inst) {
  MDNode *mdnode = inst->getMetadata("llfi_index");
  if (mdnode) {
    ConstantInt *cns_index = dyn_cast<ConstantInt>(mdnode->getOperand(0));
    return cns_index->getSExtValue();
  } else {
    errs() << "ERROR: LLFI indices for instructions are required for the pass, "
        << "please run genllfiindexpass first\n";
    exit(3);
  }
}

static long fi_index = 0;
void setLLFIIndexofInst(Instruction *inst) {
  assert (fi_index >= 0 && "static instruction number exceeds index max");
  Function *func = inst->getParent()->getParent();
  LLVMContext &context = func->getContext();
  std::vector<Value*> llfiindex(1);
  llfiindex[0] = ConstantInt::get(Type::getInt64Ty(context), fi_index++);
  MDNode *mdnode = MDNode::get(context, llfiindex);
  inst->setMetadata("llfi_index", mdnode);
}

void genFullNameOpcodeMap(
    std::map<std::string, unsigned> &opcodenamemap) {
#define HANDLE_INST(N, OPC, CLASS) \
  opcodenamemap[std::string(Instruction::getOpcodeName(N))] = N;
#include "llvm/Instruction.def"
}

}
