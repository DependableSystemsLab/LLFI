#include "RegLocBasedFIRegSelector.h"

namespace llfi {

bool RegLocBasedFIRegSelector::isRegofInstFITarget(Value *reg, 
                                                          Instruction *inst) {
  if (firegloc == dstreg) {
    return reg == inst;
  } else if (firegloc == allsrcreg) {
    return reg != inst;
  } else {
    unsigned srcindex = (unsigned) (firegloc - srcreg1);
    unsigned totalsrcregnum = inst->getNumOperands();
    if (srcindex < totalsrcregnum) {
      return inst->getOperand(srcindex) == reg;
    } else
      return false;
  }
}

}
