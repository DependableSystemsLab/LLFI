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
class _1stOpFIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {

        if(isa<CallInst>(inst))
                                {
             CallInst* CI=dyn_cast<CallInst>(inst);
         
              Function* called_func=CI->getCalledFunction();
                 if (reg == CI->getArgOperand(0))
                        {
                          std::cout<<"target is first operand of function"<<"\n" ;
                           
                        
           return true;
                        } 
       else
         return false;
                                                    
                                }
}
   };

static RegisterFIRegSelector X("only1stoperand", new _1stOpFIRegSelector());

}  
