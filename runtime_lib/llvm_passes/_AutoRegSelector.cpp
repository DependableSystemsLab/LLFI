#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

#include "llvm/IR/IntrinsicInst.h"
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



                std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);

                std::ifstream inf2("Automation2-config");
                 std::string strInput2;
                  getline(inf2, strInput2);

        if(isa<CallInst>(inst))
           {
             CallInst* CI=dyn_cast<CallInst>(inst);
               Function* called_func=CI->getCalledFunction();

                                           
                
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
                                        // ((strInput=="RaceCondition")  && (reg == CI->getArgOperand(0)))||      
                                          ((strInput=="APIWrongFormat") && (reg == CI->getArgOperand(1)))||
                                            ((strInput=="MPIBufferOverflow") && (reg == CI->getArgOperand(2)))||
                                              ((strInput=="MPINoDrain") && (reg == CI->getArgOperand(3)))||
                                              ((strInput=="MPINoMessage") && (reg == CI->getArgOperand(1)))||
                                                ((strInput=="MPIInvalidMessage") && (reg == CI->getArgOperand(1)))||
                                                 ((strInput=="MPIDeadLock")   && (reg == CI->getArgOperand(0)))|| 
                                                  ((strInput=="MPIInvalidSender")   && (reg == CI->getArgOperand(1)))|| 
                                                   ((strInput=="DataCorruption")  && (reg == CI->getArgOperand(0)))||  
                                                   ((strInput=="MemMemoryLeak") && (reg == CI->getArgOperand(0))))
                                       
                   {
                          std::cout<<"target is automatically selected"<<"\n" ;
                           
                       
           return true;
                   }

  else if  (strInput=="WrongSavedAddress")
           {  
                if (called_func->getName()=="fread")
               {
                  if (reg == CI->getArgOperand(0))
                   {
                  std::cout<<"target is fread0"<<"\n";
                  return true;
                   }
               } 

              else if (called_func->getName()=="fwrite")   
               {
                 if ( reg == CI->getArgOperand(3))
                  {
                  std::cout<<"target is fwrite3"<<"\n";
                  return true;
                  }
               } 
                         
             return true ; 
           }    



else if  (strInput=="WrongRetrievedAddress") 
           {  
                if (called_func->getName()=="fwrite")
               {
                  if (reg == CI->getArgOperand(0))
                   { 
                  std::cout<<"target is fwrite0"<<"\n";
                  return true;
                   }
               } 

              else if (called_func->getName()=="fread")   
               {
                 if ( reg == CI->getArgOperand(3))
                    {
                  std::cout<<"target is fread3"<<"\n";
                  return true;
                    }
               } 
                         
             return true ; 
           }    





      /*  else if (strInput=="MemBufOverflow")
           {  
                if (called_func->getName()=="malloc")
               {
                  reg = CI->getArgOperand(0);
                  std::cout<<"target is malloc size"<<"\n";
                  return true;
               } 

              else if ((called_func->getName()=="llvm.memcpy.p0i8.p0i8.i64")   ||  
                     (called_func->getName()=="llvm.memmove.p0i8.p0i8.i64") )
               {
                  reg = CI->getArgOperand(2);
                  std::cout<<"target is memcpy/memmove size"<<"\n";
                  return true;
               } 
                         
             return true ; threa
           }     */

       
        else if ((strInput=="APIInappropriateClose")||(strInput2=="HighFrequentEvent-on-IO")||(strInput=="RaceCondition") )
           {  
            if (reg==CI)
               {std::cout<<"target is destination register"<<"\n";
             return true ; 
               }
           }


        else if ((strInput=="MEMStalePointer") ||(strInput=="MEMExhaustion")||(strInput=="MEMInvalidPointer")||(strInput=="LowMemory")|| (strInput=="MPINoAck") )
           {  
            if (reg==CI)
               {std::cout<<"target is destination register:"<<"\n";
             return true ; 
               }
           }

        else if (strInput=="CFL") 
           {  
            if (reg==CI)
               {std::cout<<"target is destination register:"<<"\n";
             return true ; 
               }
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

                if (called_func->getName()==funcName[j].c_str())
               {
                  if (reg == CI->getArgOperand(ArgPosNumber[j]))
                  {
                  std::cout<<"target is :"<<funcName[j]<<" "<<ArgPosNumber[j]<<"\n";
                  return true;
                  }
               } 
             }    
           }



  /*  else  if (strInput=="MPIInvalidMessage")
          



       {
          

        std::string line;
	string funcName[10];
	int   ArgPosNumber[10];
        std::ifstream inFile;
	inFile.open ("MPI-InvalidMessage-Config.txt");
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
 
                if (called_func->getName()==funcName[j].c_str())
               {
                 if ( reg == CI->getArgOperand(ArgPosNumber[j]));
                 { std::cout<<"target is :"<<funcName[j]<<" "<<ArgPosNumber[j]<<"\n";
                  return true;}
               } 
             }



    
           }


*/

       }
       else if ((strInput=="CPUHogTarget")||(strInput=="HighFrequentEvent-on-RETURN")) 
              {
 
                 if (isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                                ReturnInst* RI=dyn_cast<ReturnInst>(TI);
                                                    if (reg==RI->getReturnValue());
                                                     }         std::cout<<"target is return value of function"<<"\n" ;                                                                                       
                                                      return true;
                                                     {
                                            }
                                 }
              }
                  




      else if ((strInput=="APINoOutput")||(strInput=="DataNoOutput")||(strInput=="DataIncorrectOutput")||(strInput=="APIIncorrectOutput"))
              {
 
                 if (isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                                ReturnInst* RI=dyn_cast<ReturnInst>(TI);
                                                   if (RI->getParent()->getParent()->getName()!="main")
                                                       {
                                                         if (reg==RI->getReturnValue())
                                                         {
                                                              std::cout<<"target is return value of function"<<"\n" ;                                                                                       
                                                           return true;
                                                         }
                                                       }
                                            }
                                 }
              }                                 
             
         return false;
                                                    
                                
}
   };

static RegisterFIRegSelector X("Automatic", new _AutoRegSelector());

}  

 
