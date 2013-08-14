#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"

using namespace llvm;

namespace llfi {

/**
 * This sample instruction selector only selects instructions in function main
 */
// TODO: enable custom selctor to have more sources of options, e.g. read from
// config file
class SampleFIInstSelector: public FIInstSelector {
 private:
  virtual bool isInstFITarget(Instruction *inst) {
    if (inst->getParent()->getParent()->getName() == "main")
      return true;
    else
      return false;
  }
};

static RegisterFIInstSelector X("onlymain", new SampleFIInstSelector());
}
