#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
class AutoInjection: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {


   std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
                   //std::cout<<strInput<<"\n";
           
        if ((strInput=="APINoOpen")||(strInput=="APINoClose")||(strInput=="APIWrongFile")||(strInput=="APIWrongMode")||(strInput=="APIWrongPointer")||(strInput=="MemMemoryLeak")||(strInput=="MemWrongSource")||(strInput=="MemWrongDestination"))
      
        {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] ^= 0x1 << fi_bitpos;
    std::cout<<"bit flip injected"<<"\n" ;
    
        }	
 
       else  if ((strInput=="APIBufferOverflow")||(strInput=="MemBufOverflow2")|| (strInput=="MemUnderAccumulator") )
       {
        int diff=2500000;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf + diff;
            buf= (char*)newbuf;
         std::cout<<"IncValue injected"<<"\n" ;
        }

       else if ((strInput=="APIBufferUnderflow")||(strInput=="MemBufOverflow1"))

       {
       int diff=10;
         int* newbuf= (int*)buf;
          *newbuf=*newbuf - diff;
            buf= (char*)newbuf;
         std::cout<<"DecValue injected"<<"\n" ;
         std::cout<<"New size is:"<< *newbuf<<"\n" ;
       }

      else if (strInput=="APIInappropriateClose")

      {
               FILE* p= (FILE*) buf ;
                     fclose(p);
            std::cout<<"noOpen_API injected"<<"\n" ;
      }

      else  
      std::cout<<"nothing injected"<<"\n" ;
      inf.close();     
  }
};


static RegisterFaultInjector X("AutoInjection", new AutoInjection());



