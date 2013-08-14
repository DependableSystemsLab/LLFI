#ifndef FI_CUSTOM_INST_SELECTOR_MANAGER_H
#define FI_CUSTOM_INST_SELECTOR_MANAGER_H

#include <iostream>
#include <map>
#include <string>

namespace llfi {
class FIInstSelector;
class FIRegSelector;

class FICustomInstSelectorManager {
 public:
  FICustomInstSelectorManager() {}

 public:
  static FICustomInstSelectorManager *getCustomInstSelectorManager();
  void addCustomInstSelector(const std::string &name, 
                             FIInstSelector *instselector);
  FIInstSelector *getCustomInstSelector(const std::string &name);

 private:
  std::map<const std::string, FIInstSelector* > optionname_instselector;
};


class FICustomRegSelectorManager {
 public:
  FICustomRegSelectorManager() {}

 public:
  static FICustomRegSelectorManager *getCustomRegSelectorManager();
  void addCustomRegSelector(const std::string &name, 
                            FIRegSelector *regselector);
  FIRegSelector *getCustomRegSelector(const std::string &name);

 private:
  std::map<const std::string, FIRegSelector* > optionname_regselector;
};


// helper class to register custom inst or reg selector
struct RegisterFIInstSelector {
  RegisterFIInstSelector(const std::string &name, FIInstSelector *sel) {
    FICustomInstSelectorManager *m = 
        FICustomInstSelectorManager::getCustomInstSelectorManager();
    m->addCustomInstSelector(name, sel);
  }
};

struct RegisterFIRegSelector {
  RegisterFIRegSelector(const std::string &name, FIRegSelector *sel) {
    FICustomRegSelectorManager *m =
        FICustomRegSelectorManager::getCustomRegSelectorManager();
    m->addCustomRegSelector(name, sel);
  }
};

}
#endif
