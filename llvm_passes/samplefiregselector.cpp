#include "llvm/Value.h"
#include "llvm/Instruction.h"
#include "llvm/Constants.h"

#include "firegselector.h"
#include "ficustomselectormanager.h"

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
