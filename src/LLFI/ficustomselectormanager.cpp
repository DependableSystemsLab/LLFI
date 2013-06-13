#include "llvm/Support/raw_ostream.h"

#include "fiinstselector.h"
#include "firegselector.h"
#include "ficustomselectormanager.h"

namespace llfi {

FICustomInstSelectorManager
    *FICustomInstSelectorManager::getCustomInstSelectorManager() {
  static FICustomInstSelectorManager instsel_manager;
  return &instsel_manager;  
}

void FICustomInstSelectorManager::addCustomInstSelector(
    const std::string &name, FIInstSelector *instselector) {
  if (optionname_instselector.find(name) == optionname_instselector.end()) {
    optionname_instselector[name] = instselector;
  } else {
    errs() << "Duplicate custom fault injection instruction selector: " <<
        name << "\n";
    exit(1);
  }
}

FIInstSelector *FICustomInstSelectorManager::getCustomInstSelector(
    const std::string &name) {
  if (optionname_instselector.find(name) != optionname_instselector.end()) {
    return optionname_instselector[name];
  } else {
    errs() << "Invalid custom fault injection instruction selector: " <<
        name << "\n";
    exit(1);
  }
}


// fault injection register selector manager
FICustomRegSelectorManager
    *FICustomRegSelectorManager::getCustomRegSelectorManager() {
  static FICustomRegSelectorManager regsel_manager;
  return &regsel_manager;
}

void FICustomRegSelectorManager::addCustomRegSelector(
    const std::string &name, FIRegSelector *regselector) {
  if (optionname_regselector.find(name) == optionname_regselector.end()) {
    optionname_regselector[name] = regselector;
  } else {
    errs() << "Duplicate custom fault injection register selector: " <<
        name << "\n";
    exit(1);
  }
}

FIRegSelector *FICustomRegSelectorManager::getCustomRegSelector(
    const std::string &name) {
  if (optionname_regselector.find(name) != optionname_regselector.end()) {
    return optionname_regselector[name];
  } else {
    errs() << "Invalid custom fault injection register selector: " <<
        name << "\n";
    exit(1);
  }
}

}
