#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class IncreasedValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
    long diff= 100;
       std::cin>> diff;  
         *buf=*buf + diff;
           std::cout<< *buf;
  }
};


static RegisterFaultInjector X("increasedvalue", new IncreasedValue());

