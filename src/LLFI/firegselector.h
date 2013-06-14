#ifndef FI_REG_SELECTOR_H
#define FI_REG_SELECTOR_H
#include "llvm/Instruction.h"
#include "llvm/Value.h"

#include <set>
#include <map>
#include <list>

using namespace llvm;
namespace llfi {
class FIRegSelector {
 public:
  void getFIInstRegMap(const std::set< Instruction* > *instset, 
                std::map<Instruction*, std::list< Value* >* > *instregmap);

 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) = 0;

  // determine whether LLFI is able to inject into the specified reg or not
  bool isRegofInstInjectable(Value *reg, Instruction *inst);
};

}

#endif
