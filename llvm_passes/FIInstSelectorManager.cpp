#include "llvm/IR/Instructions.h"

#include "FIInstSelectorManager.h"

namespace llfi {

void FIInstSelectorManager::getFIInsts(Module &M,
                                         std::set<Instruction*> *fiinsts) {
  // Create a set for each selector and print compiletime info
  std::vector<std::set<Instruction*>*> allInsts;
  for(it = selectors.begin(); it != selectors.end(); ++it) {
    allInsts.push_back(new std::set<Instruction*>);
     std::map<std::string, std::string> info;
     (*it)->getCompileTimeInfo(info);
     printCompileTimeInfo(info);
     (*it)->getFIInsts(M, allInsts.back());
  }

  // Merge allInsts into fiinsts
  std::set<Instruction*> merge = *(allInsts[0]);
  for(size_t i = 1; i < allInsts.size(); ++i) {
    std::set<Instruction*> tmp;
    tmp.swap(merge);
    std::set_intersection(tmp.begin(), tmp.end(),
                          allInsts[i]->begin(), allInsts[i]->end(),
                          std::inserter(merge, merge.begin()));
  }

  fiinsts->swap(merge);

  for(size_t i = 0; i < allInsts.size(); ++i) {
    delete allInsts[i];
  }
}

int FIInstSelectorManager::printCompileTimeInfo(std::map<std::string, std::string>& info) {
  // print compiletime info returned from inst selector, called by getFIInsts()
  std::ofstream compiletimeinfo_file("llfi.config.compiletime.txt");
  if(compiletimeinfo_file.is_open() == false){
    std::cerr<<"ERROR: can not open llfi.config.compiletime.txt\n";
    compiletimeinfo_file.close();
    return -1;
  }
  compiletimeinfo_file<<"failure_class="<<info["failure_class"]<<"\n";
  compiletimeinfo_file<<"failure_mode="<<info["failure_mode"]<<"\n";
  compiletimeinfo_file<<"targets="<<info["targets"]<<"\n";
  compiletimeinfo_file<<"injector="<<info["injector"]<<"\n";
  compiletimeinfo_file.close();
  return 0;
}

void FIInstSelectorManager::addSelector(FIInstSelector *s)
{
  selectors.push_back(s);
}

void FIInstSelectorManager::setIncludeBackwardTrace(bool includebt)
{
  for(size_t i = 0; i < selectors.size(); ++i) {
    selectors[i]->setIncludeBackwardTrace(includebt);
  }

}
void FIInstSelectorManager::setIncludeForwardTrace(bool includeft)
{
  for(size_t i = 0; i < selectors.size(); ++i) {
    selectors[i]->setIncludeForwardTrace(includeft);
  }
}

FIInstSelectorManager::FIInstSelectorManager()
{

}

FIInstSelectorManager::~FIInstSelectorManager()
{
  for(it = selectors.begin(); it != selectors.end(); ++it) {
    delete *it;
  }
}

}
