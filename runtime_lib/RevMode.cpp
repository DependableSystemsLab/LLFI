#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class ReverseMode: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
       FILE *fp;
      char *newMode;
       fp=fopen("newMode-config","r");
         *newMode=fgetc(fp);
         fclose(fp);
         // std::cin>> newMode;
      
           *buf= *newMode; 
          
         
          
         
                                }
};


static RegisterFaultInjector X("RevMode", new ReverseMode());

