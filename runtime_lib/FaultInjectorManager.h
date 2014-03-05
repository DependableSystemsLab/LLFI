#ifndef FAULT_INJECTOR_MANAGER_H
#define FAULT_INJECTOR_MANAGER_H

#include <iostream>
#include <map>
#include <string>

#include <stdio.h>
#include <cstdlib>

#include "Utils.h"

class FaultInjector;
class FaultInjectorManager {
 public:
  FaultInjectorManager() {}

 public:
  static FaultInjectorManager *getFaultInjectorManager();
  void addFaultInjector(const std::string &name,
                        FaultInjector *fi);
  FaultInjector *getFaultInjector(const std::string &name);

 private:
  std::map<const std::string, FaultInjector* > type_injector;
};

struct RegisterFaultInjector {
  RegisterFaultInjector(const std::string &name, FaultInjector *fi) {
    //debug(( "init\n"));
    FaultInjectorManager *m = FaultInjectorManager::getFaultInjectorManager();
    //debug(("get manager\n"));
    m->addFaultInjector(name, fi);
    //debug(("finish\n"));
  }
};

#endif
