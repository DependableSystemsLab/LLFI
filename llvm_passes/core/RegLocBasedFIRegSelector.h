#ifndef REGLOC_BASED_FI_REG_SELECTOR_H
#define REGLOC_BASED_FI_REG_SELECTOR_H

#include "Controller.h"
#include "FIRegSelector.h"
namespace llfi {
class RegLocBasedFIRegSelector: public HardwareFIRegSelector {
 public:
  RegLocBasedFIRegSelector(FIRegLoc filoc): firegloc(filoc) {}

 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst);
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst, int pos);
 private:
  FIRegLoc firegloc;
};
}



#endif
