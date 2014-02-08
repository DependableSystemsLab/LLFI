#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
class WrongFormat: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
   
    
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
};


static RegisterFaultInjector X("WrongFormat", new WrongFormat());

