#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class BlockedOutput: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
  for( ; ; )
   {
      std::cout<<"This loop will run forever!!"<<"\n";
   }

                                                     }
};


static RegisterFaultInjector X("BlockedOutput", new BlockedOutput());

