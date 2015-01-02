#ifndef FI_INST_SELECTOR_MANAGER_H
#define FI_INST_SELECTOR_MANAGER_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "FIInstSelector.h"

using namespace llvm;
namespace llfi {

class FIInstSelectorManager {
 public:
  FIInstSelectorManager();
  ~FIInstSelectorManager();
  void addSelector(FIInstSelector *s);
  void getFIInsts(Module &M, std::set<Instruction*> *fiinsts);

  void setIncludeBackwardTrace(bool includebt);
  void setIncludeForwardTrace(bool includeft);

 private:
  std::vector<FIInstSelector*> selectors;
  std::vector<FIInstSelector*>::iterator it;

  int printCompileTimeInfo(std::map<std::string, std::string>& info);
};

}

#endif
