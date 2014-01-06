#include "llvm/IR/Value.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Constants.h"

#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

namespace llfi {

/**
 * This sample register selector only selects constant int as target
 */
class SampleFIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {
    if (isa<ConstantInt>(reg))
      return true;
    else
      return false;
  }
};

static RegisterFIRegSelector X("onlyconstint", new SampleFIRegSelector());

}
