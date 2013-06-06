
#include "indexbasedfiregselector.h"

namespace llfi {

// TODO: avoid the allsrcreg for now, as it is not well validated against
// real world examples

bool IndexBasedFIRegSelector::isRegofInstFITarget(Value *reg, 
                                                          Instruction *inst) {
  if (firegloc == dstreg) {
    return reg == inst;
  } else if (firegloc == allsrcreg) {
    // TODO: the option is not supported for now, need to think about it
    return false;
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
