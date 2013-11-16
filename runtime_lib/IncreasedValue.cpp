#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class IncValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
       
       int diff=2500;
 //  FILE *fp;
      //  fp=fopen("diff-config","r");
      //   diff=fgetc(fp);
       //   fclose(fp);
//std::cin>>diff;
       
     int* newbuf= (int*)buf;
       *newbuf=*newbuf + diff;
            buf= (char*)newbuf;
    
  
              
         
  }
};


static RegisterFaultInjector X("IncValue", new IncValue());

