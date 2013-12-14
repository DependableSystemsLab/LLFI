
#include "llvm/Instructions.h"

#include "FuncNameFIInstSelector.h"
#include "Utils.h"

namespace llfi {

bool FuncNameFIInstSelector::isInstFITarget(Instruction *inst) {
  std::string func = inst->getParent()->getParent()->getName();
  func = demangleFuncName(func);

  if (funclist->find(func) != funclist->end()) {
    return true;
  }
  return false;
}

}
