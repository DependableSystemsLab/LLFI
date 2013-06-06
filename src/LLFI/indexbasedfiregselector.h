#ifndef INDEX_BASED_FI_REG_SELECTOR_H
#define INDEX_BASED_FI_REG_SELECTOR_H

#include "controller.h"
#include "firegselector.h"
namespace llfi {
class IndexBasedFIRegSelector: public FIRegSelector {
 public:
  IndexBasedFIRegSelector(FIRegLoc filoc): firegloc(filoc) {}

 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst);

 private:
  FIRegLoc firegloc;
};
}



#endif
