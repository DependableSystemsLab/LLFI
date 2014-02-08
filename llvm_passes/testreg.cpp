#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

#include "llvm/IntrinsicInst.h"


namespace llfi {

/**
 * This register selector only selects the first operand of call function as target
 */
class testreg: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst)         

  {
                          if(isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                                ReturnInst* RI=dyn_cast<ReturnInst>(TI);
                                               if  (reg==RI->getReturnValue()&& (RI->getParent()->getParent()->getName()!="main"))
                                              
                                                      { 
                                                     std::cout<<"reg"<<reg<<"\n" ;  
                                                     std::cout<<"target is return value of function"<<"\n" ;                                                                                       
                                                      return true;
                                                      }
                                                   
                                            }
                                }
                                            else
                                            return false;

                                 
          }   

                                              
   };

static RegisterFIRegSelector X("testreg", new testreg());

}  
