
#include "llvm/Instructions.h"

#include "FIInstSelectorManager.h"

namespace llfi {

void FIInstSelectorManager::getFIInsts(Module &M,
                                         std::set<Instruction*> *fiinsts) {
  // Create a set for each selector 
  std::vector<std::set<Instruction*>*> allInsts;
  for(it = selectors.begin(); it != selectors.end(); ++it) {
    allInsts.push_back(new std::set<Instruction*>);
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
