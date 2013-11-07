#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"


namespace llfi {

/**
 * This register selector only selects the 4th operand of call function as target
 */
class _4thOpFIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {

        if(isa<CallInst>(inst))
                                {
             CallInst* CI=dyn_cast<CallInst>(inst);
         
              Function* called_func=CI->getCalledFunction();
                 if (reg == CI->getArgOperand(3))
                        {
                          std::cout<<"target is 4th operand of function"<<"\n" ;
                           
                        
           return true;
                        } 
       else
         return false;
                                                    
                                }
}
   };

static RegisterFIRegSelector X("only4thoperand", new _4thOpFIRegSelector());

}  
