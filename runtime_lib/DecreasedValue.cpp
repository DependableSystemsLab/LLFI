#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class DecValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
   
       int diff;
   FILE *fp;
        fp=fopen("diff-config","r");
         diff=fgetc(fp);
          fclose(fp);

       
     int* newbuf= (int*)buf;
       *newbuf=*newbuf - diff;
            buf= (char*)newbuf;
    
    *buf=*buf-diff;
              
  }
};


static RegisterFaultInjector X("DecValue", new DecValue());

