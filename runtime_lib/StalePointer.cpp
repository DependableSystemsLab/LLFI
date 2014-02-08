#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class StalePointer: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
                
                printf(" Pointer is used after being freed \n");
                  void* x= (void*)(*buf);
                     free(x);
                       std::cout<<"Stale Pointer injected"<<"\n";
              }
};


static RegisterFaultInjector X("StalePointer", new StalePointer());

