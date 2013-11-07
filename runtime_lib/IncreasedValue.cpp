#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class IncValue: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
       FILE *fp;
      int diff;
        fp=fopen("diff-config","r");
         diff=fgetc(fp);
          fclose(fp);
     //  int * newbuf=dyn_cast<int>(buf);
         int* newbuf= (int*)buf;
      *newbuf=*newbuf + diff;
     //char *buf=dyn_cast<char>(newbuf);
        buf= (char*)newbuf;
              
         
  }
};


static RegisterFaultInjector X("IncValue", new IncValue());

