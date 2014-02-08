#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class MemoryExhaustion: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
 
         int* newbuf= (int*)buf;
           int i=0;        
           char* temp_ptr;
       do {
           i++;
            int diff=1000000000*i;
             *newbuf= *newbuf+ diff;
             temp_ptr=(char*)malloc(*newbuf);
               std:: cout << static_cast<void *>(temp_ptr) << "\n";
                 free(temp_ptr);

          }while (temp_ptr != NULL);
          
            buf= (char*)newbuf;
         std::cout<< "ExhaustMem injected"<<"\n" ; 
         std::cout<<"New value is:"<< *newbuf<<"\n" ;
            temp_ptr=(char*)malloc(*newbuf);
                  buf= temp_ptr;
    
                                }
};


static RegisterFaultInjector X("MemoryExhaustion(MEM)", new MemoryExhaustion());

