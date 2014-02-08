#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class DeadLock: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
	
 
         /*int* newbuf= (int*)buf;
           int i=0;        
            std::cout<< "LowMemory injected"<<"\n" ; 
         std::cout<<"New value is:"<< *newbuf<<"\n" ;*/



 pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
  
	        pthread_mutex_lock( &mutex1 );
                 pthread_t thread1= *buf;
                   pthread_join(thread1,NULL);
                    pthread_mutex_lock( &mutex1 );
                     std::cout<< "DeadLoak injected"<<"\n" ; 
                      *buf= char (thread1);
                                                     }
};


static RegisterFaultInjector X("DeadLock", new DeadLock());

