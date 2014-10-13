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
  virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
    info["failure_class"] = "HardwareFault";
    info["failure_mode"] = "SpecifiedFunctions";
    for(std::set<std::string>::iterator SI = funclist->begin();
      SI != funclist->end(); SI++){
      info["targets"] += *SI + "()/";
    }
    //remove the '/' at the end
    info["targets"] = info["targets"].substr(0, info["targets"].length()-1);
    info["injector"] = "<fi_type>";
  }

 private:
  virtual bool isInstFITarget(Instruction* inst);

 private:
  std::set<std::string> *funclist;
};

}



#endif
