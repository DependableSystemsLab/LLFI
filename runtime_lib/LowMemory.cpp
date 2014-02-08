#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class LowMemory: public FaultInjector {
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
            *newbuf= *newbuf-30;
             temp_ptr=(char*)malloc(*newbuf);
           // buf= (char*)newbuf;
            buf=temp_ptr;
         std::cout<< "LowMemory injected"<<"\n" ; 
         std::cout<<"New value is:"<< *newbuf<<"\n" ;
                      
             
            
               
    
                                }
};


static RegisterFaultInjector X("LowMemory(MEM)", new LowMemory());

