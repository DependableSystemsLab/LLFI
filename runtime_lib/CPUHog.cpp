#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class CPUHog: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
              /* FILE* fp= fopen ("text.txt","r"); 
               char ch;
               for(;;) { ch=fgetc(fp); if(ch=='~') { break; } }
	       fclose (fp);*/
            sleep (3);  
                
           std::cout<< "CPUHog injected"<<"\n" ;
 
            
                                                    }
};


static RegisterFaultInjector X("CPUHog", new CPUHog());

