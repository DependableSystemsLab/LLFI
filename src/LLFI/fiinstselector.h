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
  // virtual in case instruction selection on source needs to rewrite
  virtual void getFIInsts(Module &M, std::set<Instruction*> *fiinsts);
  
 private:
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
