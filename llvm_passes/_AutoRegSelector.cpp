#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

#include "llvm/IntrinsicInst.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
namespace llfi {

/**
 * This register selector only selects target register automatically 
 */
class _AutoRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {

        if(isa<CallInst>(inst))
           {
             CallInst* CI=dyn_cast<CallInst>(inst);
               Function* called_func=CI->getCalledFunction();

                                           
                std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (((strInput=="APINoOpen") && (reg == CI->getArgOperand(0)))||
                ((strInput=="APINoClose") && (reg == CI->getArgOperand(0))) ||
                 ((strInput=="APIWrongFile") && (reg == CI->getArgOperand(3)))||
                   ((strInput=="APIBufferOverflow") && (reg == CI->getArgOperand(2)))||
                     ((strInput=="APIBufferUnderflow") && (reg == CI->getArgOperand(2)))||
                       ((strInput=="APIWrongMode") && (reg == CI->getArgOperand(1)))||
                         ((strInput=="APIWrongPointer") && (reg == CI->getArgOperand(0)))||
                           ((strInput=="MemWrongDestination") && (reg == CI->getArgOperand(0)))||
                             ((strInput=="MemWrongSource") && (reg == CI->getArgOperand(1)))||
                               ((strInput=="MemUnderAccumulator") && (reg == CI->getArgOperand(0)))||
                                 ((strInput=="MemBufOverflow1") && (reg == CI->getArgOperand(0)))||
                                   ((strInput=="MemBufOverflow2") && (reg == CI->getArgOperand(2)))||
                                     ((strInput=="MemDeadLock") && (reg == CI->getArgOperand(0)))||
                                       ((strInput=="MemThreadKiller") && (reg == CI->getArgOperand(0)))||
                                        ((strInput=="APIWrongFormat") && (reg == CI->getArgOperand(1)))||   
                                         ((strInput=="MemMemoryLeak") && (reg == CI->getArgOperand(0))))
                                       
                   {
                          std::cout<<"target is automatically selected"<<"\n" ;
                           
                       
           return true;
                   }
        else if (strInput=="APIInappropriateClose") 
           {  
            reg=inst;
            std::cout<<"target is file pointer:"<< reg<<"\n";
             return true ; 
           }

        else if ((strInput=="MEMStalePointer") ||(strInput=="MEMExhaustion")||(strInput=="MEMInvalidPointer")||(strInput=="LowMemory"))
           {  
            reg=inst;
            std::cout<<"target is malloc pointer:"<< reg<<"\n";
             return true ; 
           }
       

        else  if (strInput=="APIWrongAPI")
           {
          

                 std::string line;
	string funcName[10];
	int   ArgPosNumber[10];


	std::ifstream inFile;

	inFile.open ("API-Config.txt");
	int i = 0;

        
    
	while(getline(inFile, line))

	{
                 
     
		std::stringstream dosString;
		dosString<<line;
		dosString>> funcName[i]>>ArgPosNumber[i];
                i++;

	}
 //std::cout<<"debugger:"<<"\n";
	        for (int j = 0;  j< i; j++)
	      {

                if ((reg == CI->getArgOperand(ArgPosNumber[j])))    //  (called_func->getName()==funcName[j].c_str())
             { std::cout<<"target is :"<<funcName[j]<<" "<<ArgPosNumber[j]<<"\n";
              
             return true;}
              } 
         }    
       
/*else if (strInput=="MemThreadKiller") 
           {  
            reg=inst;
            std::cout<<"target is pthread_create pointer:"<< reg<<"\n";
             return true ; 
           }    */







       }
       else if(isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                                ReturnInst* RI=dyn_cast<ReturnInst>(TI);

                                                  std::ifstream inf("Automation-config");
                                                    std::string strInput;
                                                     getline(inf, strInput);
                                                       if ((strInput=="CPUHogTarget") && (reg==RI->getReturnValue()))
                                                                                         
                                                      { 
                                                      std::cout<<"target is return value of function"<<"\n" ;                                                                                       
                                                      return true;
                                                      }
                                                   
else if (((strInput=="APINoOutput")||(strInput=="DataNoOutput")||(strInput=="DataIncorrectOutput")||(strInput=="DataIncorrectOutput")) && (reg==RI->getReturnValue())&&((RI->getParent()->getParent()->getName()!="main")));
                                                                                         
                                                      { 
                                                      std::cout<<"target is return value of function"<<"\n" ;                                                                                       
                                                      return true;
                                                      }
                                                    
                                                      
                                            }
                                 }
         return false;
                                                    
                                
}
   };

static RegisterFIRegSelector X("Automatic", new _AutoRegSelector());

}  

 
