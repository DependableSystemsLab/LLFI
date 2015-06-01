#ifndef FI_INST_SELECTOR_H
#define FI_INST_SELECTOR_H
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"

#include <set>

using namespace llvm;

namespace llfi {
class FIInstSelector {
 public:
  FIInstSelector(): includebackwardtrace(false), includeforwardtrace(false) {}

 public:
  void getFIInsts(Module &M, std::set<Instruction*> *fiinsts);
  virtual void getCompileTimeInfo(std::map<std::string, std::string>& info);

  virtual std::string getInstSelectorClass(){
    return std::string("Unknown");
  }

 public:
  inline void setIncludeBackwardTrace(bool includebt) {
    includebackwardtrace = includebt;
  }
  inline void setIncludeForwardTrace(bool includeft) {
    includeforwardtrace = includeft;
  }
  
 private:
  // get the initial fault injection instruction without backtrace or forward
  // trace, selection from source code may need to rewrite this function
  virtual void getInitFIInsts(Module &M, std::set<Instruction*> *fiinsts);

  virtual bool isInstFITarget(Instruction* inst) = 0;

 protected:
  // only get the "instructions" that are the backward/forward trace of inst
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

class SoftwareFIInstSelector: public FIInstSelector{
  virtual std::string getInstSelectorClass(){
    return std::string("SoftwareFault");
  }
};

class HardwareFIInstSelector: public FIInstSelector{
  virtual std::string getInstSelectorClass(){
    return std::string("HardwareFault");
  }
};
}

#endif
