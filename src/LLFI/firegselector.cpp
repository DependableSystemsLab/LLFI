#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Type.h"

#include "firegselector.h"

using namespace llvm;

namespace llfi {

void FIRegSelector::getFIInstRegMap(
    std::set< Instruction* > *instset, 
    std::map<Instruction*, std::list< Value* >* > *instregmap) {
  for (std::set<Instruction*>::const_iterator inst_it = instset->begin();
       inst_it != instset->end(); ++inst_it) {
    Instruction *inst = *inst_it;
    std::list<Value*> *reglist = new std::list<Value*>();
    // dstination register
    if (isRegofInstFITarget(inst, inst)) {
      if (isRegofInstInjectable(inst, inst))
        reglist->push_back(inst);
      else {
        DEBUG(errs() << "LLFI cannot inject faults in destination of " << *inst
              << "\n");
      }
    }
    // source register
    for (User::op_iterator op_it = inst->op_begin(); op_it != inst->op_end();
         ++op_it) {
      Value *src = *op_it;
      if (isRegofInstFITarget(src, inst)) {
        if (isRegofInstInjectable(src, inst)) {
          reglist->push_back(src);
        } else {
          DEBUG(errs() << "LLFI cannot inject faults in source reg " << *src <<
                " of instruction " << *inst << "\n");
        }
      }
    }
    if (reglist->size() != 0) {
      instregmap->insert(
          std::pair<Instruction*, std::list< Value* >* >(inst, reglist));
    } else {
      DEBUG(errs() << "The instruction does not have valid regs for injection" 
            << *inst << "\n");
    }
  }
}

bool FIRegSelector::isRegofInstInjectable(Value *reg, Instruction *inst) {
  // TODO: keep updating
  // if we find anything that can be covered, remove them from the checks
  // if we find new cases that we cannot handle, add them to the checks
  if (reg == inst) {
    if (inst->getType()->isVoidTy()) {
      return false;
    }
  }
  return true;
}

}
