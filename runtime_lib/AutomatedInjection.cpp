#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
class AutoInjection: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {


   std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
                   //std::cout<<strInput<<"\n";
           
        if ((strInput=="APINoOpen")||(strInput=="APINoClose")||(strInput=="APIWrongFile")||(strInput=="APIWrongMode")||(strInput=="APIWrongPointer")||(strInput=="MemMemoryLeak")||(strInput=="MemWrongSource")||(strInput=="MemWrongDestination")||(strInput=="MEMInvalidPointer")||(strInput=="APIWrongAPI")||(strInput=="APIIncorrectOutput")||(strInput=="DataIncorrectOutput") ||(strInput=="WrongRetrievedAddress") ||(strInput=="WrongSavedAddress") )
      
        {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] ^= 0x1 << fi_bitpos;
    std::cout<<"bit flip injected"<<"\n" ;
    
        }	
 
       else  if ((strInput=="APIBufferOverflow")||(strInput=="MemBufOverflow2")|| (strInput=="MemUnderAccumulator"))
       {
        int diff=45;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + diff;
            buf= (char*)newbuf;
         std::cout<<"IncValue injected"<<"\n" ;
       //  std::cout<<"New value is:"<< *newbuf<<"\n" ;
          }
        else  if (strInput=="ReturnFunction")
       {
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + 9876;
            buf= (char*)newbuf;
         std::cout<<"wrongoutput injected & new output is:"<<*newbuf<<"\n" ;
         
        }

       else if ((strInput=="APIBufferUnderflow")||(strInput=="MemBufOverflow1"))

       {
      
 int diff=45;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf - diff;
            buf= (char*)newbuf;
         std::cout<<"DecValue injected"<<"\n" ;
       //  std::cout<<"New value is:"<< *newbuf<<"\n" ;


        
       }

      else if (strInput=="APIInappropriateClose")

      {
               FILE* p= (FILE*) (*buf) ;
                     fclose(p);
            std::cout<<"noOpen_API injected"<<"\n" ;
      }

      else if (strInput=="MEMStalePointer")

      {
              
                         /*       *buf=0;
                         std::cout<<"memexhaustion injected"<<"\n" ;*/
            // FILE* p= (FILE*) buf ;
             void* x= (void*)(*buf);
                     free(x);
            std::cout<<"Stale Pointer injected"<<"\n";
      }

      else if (strInput=="MEMExhaustion")
      {
           int* newbuf= (int*)buf;
            int i=0;  
             
             char* temp_ptr;
             do {
                i++;
                 int diff=1000000000*i;
                  *newbuf= *newbuf+ diff;
                   temp_ptr=(char*)malloc(*newbuf);
                     free(temp_ptr);

                 }while (temp_ptr != NULL);
          
                buf= (char*)newbuf;
                 temp_ptr=(char*)malloc(*newbuf);
                   buf= temp_ptr;
                  
         std::cout<< "ExhaustMem injected"<<"\n" ; 
          std:: cout << static_cast<void *>(buf) << "\n";
          // std:: cout << *buf << "\n";
      }

 else if (strInput=="LowMemory")
      {

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
            *newbuf= *newbuf-100;
             temp_ptr=(char*)malloc(*newbuf);
           // buf= (char*)newbuf;
            buf=temp_ptr;
         std::cout<< "LowMemory injected"<<"\n" ; 
       }


else if (strInput=="MemDeadLock")
      {
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
  
	        pthread_mutex_lock( &mutex1 );
                 pthread_t thread1= *buf;
                   pthread_join(thread1,NULL);
                    pthread_mutex_lock( &mutex1 );
                      std::cout<< "DeadLoak was injected"<<"\n" ;
      }


else if (strInput=="MemThreadKiller")
      {
                void (*func_pointer)(void*);
		func_pointer = pthread_exit;
		buf = (char* )func_pointer;
                std::cout<< "ThreadKiller injected"<<"\n" ;

      }

else if (strInput=="APIWrongFormat")
      {
         int* newbuf= (int*)buf;
         std::cout<<"first format is: "<<*newbuf<<"\n";
          
         if (*newbuf==1) {std::cout<<"correct format is char"<<"\n" ;
                          *newbuf= 2;   
                            std::cout<<"wrong format is int"<<"\n" ;}

        else if (*newbuf==2) {std::cout<<"correct format is short int"<<"\n" ;
                              *newbuf= 4;   
                                std::cout<<"wrong format is long int"<<"\n" ;}

        else if (*newbuf==4) {std::cout<<"correct format is long int"<<"\n" ;
                              *newbuf= 1;   
                                std::cout<<"wrong format is char"<<"\n" ;}
        
        else if (*newbuf==8) {std::cout<<"correct format is long long"<<"\n" ;
                              *newbuf= 4;   
                                std::cout<<"wrong format is long int"<<"\n" ;}

        else if (*newbuf==10) {std::cout<<"correct format is long double"<<"\n" ;
                              *newbuf= 4;   
                                std::cout<<"wrong format is long int"<<"\n" ;}
        
        else   {  std::cout<<"unknown format"<<"\n" ;}
            buf= (char*)newbuf;
         std::cout<<"WrongFormat injected"<<"\n" ;
       }



else if (strInput=="CPUHogTarget")
      {
                sleep(3);
                std::cout<< "CPUHog injected"<<"\n" ;

      }


else if ((strInput=="APINoOutput")||(strInput=="DataNoOutput"))
      {
               for( ; ; )
               {  std::cout<<"This loop will run forever!!"<<"\n"; }
                std::cout<< "NoOutput injected"<<"\n" ;
      }

/* else if ((strInput=="APIIncorrectOutput")||(strInput=="DataIncorrectOutput"))
      {
               int* newbuf= (int*)buf;
          *newbuf=*newbuf + 9876;
            buf= (char*)newbuf;
         std::cout<<"wrongoutput injected & new output is:"<<*newbuf<<"\n" ;
      }   */


      else  
      std::cout<<"nothing injected"<<"\n" ;
      inf.close();     
  }
};


static RegisterFaultInjector X("AutoInjection", new AutoInjection());



