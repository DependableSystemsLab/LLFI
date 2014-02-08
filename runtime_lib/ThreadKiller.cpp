#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class ThreadKiller: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {

	        	std::cout<< "ThreadKiller injected"<<"\n" ;

                       /*   pthread_t *restrict thread= *buf;
                            pthread_detach(thread);
                             sleep(0.002);
                              pthread_cancel(thread);   */

	                 pthread_t thid= *buf;
                          //pthread_join(thid,NULL);
                            sleep( 0.02);
                        int ret=  pthread_cancel (thid); 
                std::cout<< "cancel result"<<ret<<"\n" ;
                        


             /*     
                void (*func_pointer)(void*);
		func_pointer = pthread_exit;
		buf = (char* )func_pointer;  
 */
 
                
 
             
                     //pthread_t tid= *buf;
               //delay (100);
             //  pthread_cancel(tid);
                                                    }
};


static RegisterFaultInjector X("ThreadKiller", new ThreadKiller());

