#include "llvm/Support/raw_ostream.h"

#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

namespace llfi {

// fault injection instruction selector manager
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
    errs() << "ERROR: Duplicate custom fault injection instruction selector: "
        << name << "\n";
    exit(1);
  }
}

FIInstSelector *FICustomInstSelectorManager::getCustomInstSelector(
    const std::string &name) {
  if (optionname_instselector.find(name) != optionname_instselector.end()) {
    return optionname_instselector[name];
  } else {
    errs() << "ERROR: Unknown custom fault injection instruction selector: "
        << name << "\n";
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
    errs() << "ERROR: Duplicate custom fault injection register selector: "
        << name << "\n";
    exit(1);
  }
}

FIRegSelector *FICustomRegSelectorManager::getCustomRegSelector(
    const std::string &name) {
  if (optionname_regselector.find(name) != optionname_regselector.end()) {
    return optionname_regselector[name];
  } else {
    errs() << "ERROR: Unknown custom fault injection register selector: " <<
        name << "\n";
    exit(1);
  }
}

}
