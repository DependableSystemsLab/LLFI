#ifndef FI_INST_SELECTOR_H
#define FI_INST_SELECTOR_H
#include "llvm/Module.h"
#include "llvm/Instruction.h"

#include <set>

using namespace llvm;

namespace llfi {
class FIInstSelector {
 public:
  FIInstSelector(): includebackwardtrace(false), includeforwardtrace(false) {}
  FIInstSelector(bool includebt, bool includeft):
      includebackwardtrace(includebt), includeforwardtrace(includeft) {}

 public:
  void getFIInsts(Module &M, std::set<Instruction*> *fiinsts);

 public:
  inline void setIncludeBackwardTrace(bool includebt) {
    includebackwardtrace = includebt;
  }
  inline void setIncludeForwardTrace(bool includeft) {
    includeforwardtrace = includeft;
  }
  
 private:
  // selection from source code may need to rewrite this function
  virtual void getInitFIInsts(Module &M, std::set<Instruction*> *fiinsts);
  virtual bool isInstFITarget(Instruction* inst) = 0;

 protected:
  void getBackwardTraceofInsts(const std::set<Instruction*> *fiinsts,
                          std::set<Instruction*> *bs);
  void getForwardTraceofInsts(const std::set<Instruction*> *fiinsts,
                          std::set<Instruction*> *fs);
  void getBackwardTraceofInst(Instruction *inst, 
                              std::set<Instruction*> *bs);
  void getForwardTraceofInst(Instruction *inst,
                             std::set<Instruction*> *fs);
 protected:
  bool includebackwardtrace;
  bool includeforwardtrace;
}; 
}

#endif
