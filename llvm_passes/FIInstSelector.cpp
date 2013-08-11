#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"

#include "FIInstSelector.h"

namespace llfi {
void FIInstSelector::getFIInsts(Module &M, std::set<Instruction*> *fiinsts) {
  getInitFIInsts(M, fiinsts);

  std::set<Instruction* > bs;
  std::set<Instruction* > fs;
  // must do both of the computation on the fiinsts, and update
  // fiinsts finally
  if (includebackwardtrace)
    getBackwardTraceofInsts(fiinsts, &bs);
  if (includeforwardtrace)
    getForwardTraceofInsts(fiinsts, &fs);

  fiinsts->insert(bs.begin(), bs.end());
  fiinsts->insert(fs.begin(), fs.end());
}

void FIInstSelector::getInitFIInsts(Module &M, 
                                    std::set<Instruction*> *fiinsts) {
  for (Module::iterator m_it = M.begin(); m_it != M.end(); ++m_it) {
    if (!m_it->isDeclaration()) {
      //m_it is a function  
      for (inst_iterator f_it = inst_begin(m_it); f_it != inst_end(m_it);
           ++f_it) {
        Instruction *inst = &(*f_it);
        if (isInstFITarget(inst)) {
          fiinsts->insert(inst);
        }
      }
    }  
  }
}

void FIInstSelector::getBackwardTraceofInsts(
    const std::set<Instruction* > *fiinsts, std::set<Instruction* > *bs) {
  for (std::set<Instruction* >::const_iterator inst_it = fiinsts->begin();
       inst_it != fiinsts->end(); ++inst_it) {
    Instruction *inst = *inst_it;
    getBackwardTraceofInst(inst, bs);
  }
}

void FIInstSelector::getForwardTraceofInsts(
    const std::set<Instruction* > *fiinsts, std::set<Instruction* > *fs) {
  for (std::set<Instruction* >::const_iterator inst_it = fiinsts->begin();
       inst_it != fiinsts->end(); ++inst_it) {
    Instruction *inst = *inst_it;
    getForwardTraceofInst(inst, fs);
  }
}

void FIInstSelector::getBackwardTraceofInst(Instruction *inst,
                                            std::set<Instruction*> *bs) {
  for (User::op_iterator op_it = inst->op_begin(); 
       op_it != inst->op_end(); ++op_it) {
    Value *src = *op_it;
    if (Instruction *src_inst = dyn_cast<Instruction>(src)) {
      if (bs->find(src_inst) == bs->end()) {
        bs->insert(src_inst);
        getBackwardTraceofInst(src_inst, bs);
      }
    }
  }
}

void FIInstSelector::getForwardTraceofInst(Instruction *inst,
                                           std::set<Instruction*> *fs) {
  for (Value::use_iterator use_it = inst->use_begin();
       use_it != inst->use_end(); ++use_it) {
    User *use = *use_it;
    if (Instruction *use_inst = dyn_cast<Instruction>(use)) {
      if (fs->find(use_inst) == fs->end()) {
        fs->insert(use_inst);
        getForwardTraceofInst(use_inst, fs);
      }
    }
  }
}

}
