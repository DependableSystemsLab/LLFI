#include "indexbasedfiregselector.h"

namespace llfi {

bool IndexBasedFIRegSelector::isRegofInstFITarget(Value *reg, 
                                                          Instruction *inst) {
  if (firegloc == dstreg) {
    return reg == inst;
  } else if (firegloc == allsrcreg) {
    // assume reg is taken from operands of the inst
    return reg != inst;
  } else {
    unsigned srcindex = (unsigned) (firegloc - srcreg1);
    unsigned totalsrcreg = inst->getNumOperands();
    if (srcindex < totalsrcreg) {
      return inst->getOperand(srcindex) == reg;
    } else
      return false;
  }
}

}
