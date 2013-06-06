#include "llvm/Support/InstIterator.h"
#include "fiinstselector.h"

namespace llfi {
void FIInstSelector::getFIInsts(Module *M, std::set<Instruction*> *fiinsts) {
  for (Module::iterator m_it = M->begin(); m_it != M->end(); ++m_it) {
    if (!m_it->isDeclaration()) {
      //m_it is a function  
      for (inst_iterator f_it = inst_begin(m_it); f_it != inst_end(m_it); ++f_it) {
        Instruction *inst = &(*f_it);
        if (isInstFITarget(inst)) {
          fiinsts->insert(inst);
        }
      }
    }  
  }
  
  // TODO: backtrace and forwardtrace
}

}
