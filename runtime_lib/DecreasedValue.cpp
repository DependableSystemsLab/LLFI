#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
class DecValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
   
     int diff=45;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf - diff;
            buf= (char*)newbuf;
         std::cout<<"DecValue injected"<<"\n" ;
         std::cout<<"New value is:"<< *newbuf<<"\n" ;

              
  }
};


static RegisterFaultInjector X("DecValue", new DecValue());

