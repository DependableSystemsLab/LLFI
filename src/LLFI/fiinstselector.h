#ifndef FI_INST_SELECTOR_H
#define FI_INST_SELECTOR_H
#include <set>

#include "llvm/Module.h"
#include "llvm/Instruction.h"

using namespace llvm;

namespace llfi {
class FIInstSelector {
 public:
  FIInstSelector(bool includebt, bool includeft):
      includebackwardtrace(includebt), includeforwardtrace(includeft) {}

 public:
  virtual void getFIInsts(Module *M, std::set<Instruction*> *fiinsts);
  
 private:
  virtual bool isInstFITarget(Instruction* inst) = 0;

 protected:
  bool includebackwardtrace;
  bool includeforwardtrace;
}; 
}

#endif
