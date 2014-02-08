#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class IncValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
       int diff=50;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + diff;
            buf= (char*)newbuf;
         std::cout<<"IncValue injected"<<"\n" ;
         std::cout<<"New value is:"<< *newbuf<<"\n" ;
  
              
         
  }
};


static RegisterFaultInjector X("IncValue", new IncValue());

