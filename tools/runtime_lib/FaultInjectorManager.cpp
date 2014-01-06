#include <iostream>
#include <cstdlib>
#include "FaultInjector.h"
#include "FaultInjectorManager.h"

FaultInjectorManager *FaultInjectorManager::getFaultInjectorManager() {
  static FaultInjectorManager fi_manager;
  return &fi_manager;
}

void FaultInjectorManager::addFaultInjector(const std::string &name,
                                            FaultInjector *fi) {
  //debug(("enter add fault injector\n"));
  if (type_injector.find(name) == type_injector.end()) {
    type_injector.insert(
        std::pair<const std::string, FaultInjector*>(name, fi));
  } else {
    std::cerr << "ERROR: Duplicated fault injector: " << name << std::endl;
    exit(1);
  }
}

FaultInjector *FaultInjectorManager::getFaultInjector(const std::string &name) {
  if (type_injector.find(name) != type_injector.end()) {
    return type_injector[name];
  } else {
    std::cerr << "ERROR: unknown fault injector: " << name << std::endl;
    exit(1);
  }
}


extern "C" void injectFaultImpl(const char *fi_type, long llfi_index, 
                                unsigned size, unsigned fi_bit, char *buf) {
  FaultInjectorManager *m = FaultInjectorManager::getFaultInjectorManager();
  FaultInjector *fi = m->getFaultInjector(fi_type);
  fi->injectFault(llfi_index, size, fi_bit, buf);
}
