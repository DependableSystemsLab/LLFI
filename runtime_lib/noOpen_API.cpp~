#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class noOpen_API: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
                int test;
               std::cin>> test;  
           printf("Incomplete reading/writing operations \n");

               FILE* p= (FILE*) buf ;
                     fclose(p);

              }
};


static RegisterFaultInjector X("noOpen_API", new noOpen_API());

