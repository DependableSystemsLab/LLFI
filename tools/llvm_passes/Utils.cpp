
#include "Utils.h"

namespace llfi {

std::string intToString(int i) {
  std::stringstream s;
  s << i;
  return s.str();
}

std::string longToString(long i) {
  std::stringstream s;
  s << i;
  return s.str();
}

Instruction *getTermInstofFunction(Function *func) {
  BasicBlock &termbb = func->back();
  Instruction *ret = termbb.getTerminator();

  assert(isa<ReturnInst>(ret) || isa<UnreachableInst>(ret) && 
         "Last instruction is not return or exit() instruction");
  return ret;
}

void getProgramExitInsts(Module &M, std::set<Instruction*> &exitinsts) {
  for (Module::iterator m_it = M.begin(); m_it != M.end(); ++m_it) {
    if (!m_it->isDeclaration()) {
      //m_it is a function  
      for (inst_iterator f_it = inst_begin(m_it); f_it != inst_end(m_it);
           ++f_it) {
        Instruction *inst = &(*f_it);
        if (CallInst *ci = dyn_cast<CallInst>(inst)) {
          Function *calledFunc = ci->getCalledFunction();
          if (calledFunc && calledFunc->hasName() && 
              calledFunc->getName().str() == "exit") {
            exitinsts.insert(inst);
          }
        }
      }
    }  
  }

  Function* mainfunc = M.getFunction("main");
  exitinsts.insert(getTermInstofFunction(mainfunc));
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
#include "llvm/IR/Instruction.def"
}

//Returns true if the function is indexed by llfi 
//(and therefore we should perform trace/fault injects on it)
bool isLLFIIndexedInst(Instruction *inst) {
  MDNode *mdnode = inst->getMetadata("llfi_index");
  if (mdnode) {
    return true;
  } else {
   return false;
 }
}

}
