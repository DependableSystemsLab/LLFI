#ifndef FUNC_NAME_FI_INST_SELECTOR_H
#define FUNC_NAME_FI_INST_SELECTOR_H
#include <set>
#include <string>

#include "FIInstSelector.h"

using namespace llvm;
namespace llfi {

class FuncNameFIInstSelector: public FIInstSelector {
 public:
  FuncNameFIInstSelector(std::set<std::string> *funclist) {
    this->funclist = funclist;
  }
  FuncNameFIInstSelector() {
    delete funclist;
  }

 private:
  virtual bool isInstFITarget(Instruction* inst);

 private:
  std::set<std::string> *funclist;
};

}



#endif
