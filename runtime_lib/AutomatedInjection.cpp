#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
class AutoInjection: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {


   std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
                   //std::cout<<strInput<<"\n";

   std::ifstream inf2("Automation2-config");
                 std::string strInput2;
                  getline(inf2, strInput2);
           
        if ((strInput=="APINoOpen")||(strInput=="APINoClose")||(strInput=="APIWrongFile")||(strInput=="APIWrongMode")||(strInput=="APIWrongPointer")||(strInput=="MemWrongSource")||(strInput=="MemWrongDestination")||(strInput=="MEMInvalidPointer")||(strInput=="APIWrongAPI")||(strInput=="APIIncorrectOutput")||(strInput=="DataIncorrectOutput") ||(strInput=="WrongRetrievedAddress") ||(strInput=="MPIInvalidSender")||(strInput=="MPIDeadLock")||(strInput=="WrongSavedAddress")||(strInput=="DataCorruption"))
      
        {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] ^= 0x1 << fi_bitpos;
   // std::cout<<"bit flip injected"<<"\n" ;
    
        }

 else  if (strInput=="MemMemoryLeak")
        {
      // std::cout<<"fault injectors entry"<<*buf<<"\n" ;
      int* fake_p= (int* )malloc (1000*sizeof(int)); 
      buf= (char*) &fake_p;
    //  std::cout<<"memory leak injected"<<*buf<<"\n" ;

        }

    
 
       else  if (strInput=="MPIInvalidMessage")
        {
       
      int* newbuf= (int*)buf;
      *newbuf=*newbuf + 1024;
      buf= (char*)newbuf;
      //std::cout<<"InvalidMessage injected"<<*buf<<"\n" ;
        }


       else  if (strInput=="MPINoDrain")
        {
       
      int* flag= (int*)buf;
      *flag=5000;
      buf= (char*)flag;
      //std::cout<<"NoDrain injected"<<*buf<<"\n" ;
        }






       else  if ((strInput=="APIBufferOverflow")||(strInput=="MemBufOverflow2")|| (strInput=="MemUnderAccumulator"))
       {
        int diff=45;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + diff;
            buf= (char*)newbuf;
         //std::cout<<"IncValue injected"<<"\n" ;
         }
        else  if (strInput=="ReturnFunction")
       {
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + 9876;
            buf= (char*)newbuf;
       //  std::cout<<"wrongoutput injected & new output is:"<<*newbuf<<"\n" ;
         
        }

       else if ((strInput=="APIBufferUnderflow")||(strInput=="MemBufOverflow1")||(strInput=="MPIBufferOverflow"))

       {
      
 int diff=4080;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf+diff;
            buf= (char*)newbuf;
        // std::cout<<"IncValue injected"<<"\n" ;
        // std::cout<<"New value is:"<< *newbuf<<"\n" ;


        
       }

      else if (strInput=="APIInappropriateClose")

      {
               FILE* p= (FILE*) (*buf) ;
                     fclose(p);
         //   std::cout<<"noOpen_API injected"<<"\n" ;
      }

      else if (strInput=="MEMStalePointer")

      {
              
                         /*       *buf=0;
                         std::cout<<"memexhaustion injected"<<"\n" ;*/
            // FILE* p= (FILE*) buf ;
             void* x= (void*)(*buf);
                     free(x);
         //   std::cout<<"Stale Pointer injected"<<"\n";
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
                  
       //  std::cout<< "MemoryExhauster injected"<<"\n" ; 
          //std:: cout << static_cast<void *>(buf) << "\n";


                                       /*     std::ofstream outf2("run-info-config.txt");
                outf2 << "Failure_Class=Resource Failure_Mode=MemoryExhaustion Function_Name=malloc Fault_Injector=MemoryExhauster" << "\n";
                outf2.close();   */
                      


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
        // std::cout<< "MemoryConsumer injected"<<"\n" ; 
       }


else if (strInput=="MemDeadLock")
      {
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
  
	        pthread_mutex_lock( &mutex1 );
                 pthread_t thread1= pthread_t(*buf);
                   pthread_join(thread1,NULL);
                     pthread_mutex_lock( &mutex1 );
                  //    std::cout<< "DeadLoaker was injected"<<"\n" ;
      }


else if (strInput=="MemThreadKiller")
      {
               int* newbuf= (int*)buf;
                   pthread_t thid= pthread_t (*buf);
                       sleep( 0.02);
                        int ret=  pthread_cancel (thid); 
                        if (ret!=0)
                std::cout<< "ThreadKiller injected"<<"\n" ;

      }

else if (strInput=="RaceCondition")
      {
                      pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;         
                  //  pthread_mutex_t* mutex = (pthread_mutex_t*) (buf);
                      pthread_mutex_unlock (&mutex);
                        
                std::cout<< "RaceConditionCreator injected"<<"\n" ;

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
        // std::cout<<"FormatModifier injected"<<"\n" ;
       }



else if ((strInput=="CPUHogTarget")||(strInput=="HighFrequentEvent-on-RETURN")||(strInput2=="HighFrequentEvent-on-IO"))
      {
                sleep(3);
                std::cout<< "CPUHogger injected"<<"\n" ;

      }


else if ((strInput=="APINoOutput")||(strInput=="DataNoOutput")||(strInput=="MPINoMessage")||(strInput=="MPINoAck"))
      {
               for( ; ; )
               {  std::cout<<"This loop will run forever!!"<<"\n"; }
              //  std::cout<< "BlockedOutput injected"<<"\n" ;
      }

/* else if ((strInput=="APIIncorrectOutput")||(strInput=="DataIncorrectOutput"))
      {
               int* newbuf= (int*)buf;
          *newbuf=*newbuf + 9876;
            buf= (char*)newbuf;
         std::cout<<"wrongoutput injected & new output is:"<<*newbuf<<"\n" ;
      }   */


      else  
      {std::cout<<"strInput is:"<<strInput<<"\n" ;
      std::cout<<"nothing injected"<<"\n" ;
      inf.close(); }    
  }
};


static RegisterFaultInjector X("AutoInjection", new AutoInjection());



