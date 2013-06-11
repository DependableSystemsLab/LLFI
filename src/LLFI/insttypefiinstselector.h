#ifndef INST_TYPE_FI_INST_SELECTOR_H
#define INST_TYPE_FI_INST_SELECTOR_H
#include <set>

#include "fiinstselector.h"

using namespace llvm;
namespace llfi {

class InstTypeFIInstSelector: public FIInstSelector {
 public:
  InstTypeFIInstSelector(std::set<unsigned> *opcodelist, bool includebt, 
                       bool includeft): FIInstSelector(includebt, includeft) {
    this->opcodelist = opcodelist;
  }

 private:
  virtual bool isInstFITarget(Instruction* inst);

 private:
  std::set<unsigned> *opcodelist;
};

}



#endif
