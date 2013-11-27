
#include "llvm/Instructions.h"

#include "FuncNameFIInstSelector.h"

namespace llfi {

bool FuncNameFIInstSelector::isInstFITarget(Instruction *inst) {
  std::string func = inst->getParent()->getParent()->getName();

  if (funclist->find(func) != funclist->end()) {
    return true;
  }
  return false;
}

}
