#ifndef INST_TYPE_FI_INST_SELECTOR_H
#define INST_TYPE_FI_INST_SELECTOR_H
#include <set>

#include "FIInstSelector.h"

using namespace llvm;
namespace llfi {

class InstTypeFIInstSelector: public HardwareFIInstSelector {
 public:
  InstTypeFIInstSelector(std::set<unsigned> *opcodelist) {
    this->opcodelist = opcodelist;
  }
  ~InstTypeFIInstSelector() {
    delete opcodelist;
  }
  virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
    info["failure_class"] = "HardwareFault";
    info["failure_mode"] = "SpecifiedInstructionTypes";
    /*for(std::set<int>::iterator SI = opcodelist.begin();
      SI != opcodelist.end(); SI++){
      info["targets"] += string(*SI) + "()/";
    }*/
    //remove the '/' at the end
    /*info["targets"] = info["targets"].substr(0, info["targets"].length()-1);*/
    info["targets"] = "<include list in yaml>";
    info["injector"] = "<fi_type>";
  }

 private:
  virtual bool isInstFITarget(Instruction* inst);
 private:
  std::set<unsigned> *opcodelist;
};

}



#endif
