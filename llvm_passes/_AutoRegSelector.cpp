#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

#include "llvm/IntrinsicInst.h"
#include <fstream>
#include <iostream>

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

          
                // if(called_func->getName()=="fopen")
                                  
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
                                     ((strInput=="MemMemoryLeak") && (reg == CI->getArgOperand(0))))
                                       
                   {
                          std::cout<<"target is automatically selected"<<"\n" ;
                           
                       
           return true;
                   }
        else if (strInput=="APIInappropriateClose") 
           {  
            // std::cout<<"CI:"<< CI<<"\n";
             // std::cout<<"inst:"<< inst<<"\n";
            reg=inst;
            std::cout<<"target is file pointer:"<< reg<<"\n";
             return true ; 
           }
       else
         return false;
                                                    
                                }
}
   };

static RegisterFIRegSelector X("Automatic", new _AutoRegSelector());

}  

 
