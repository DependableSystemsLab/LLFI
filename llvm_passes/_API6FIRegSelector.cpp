#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"


namespace llfi {

/**
 * This register selector only selects the third operand of write function as target
 */
class _API6FIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {
    

         if(isa<CallInst>(inst))
                                {
             CallInst* CI=dyn_cast<CallInst>(inst);
         
              Function* called_func=CI->getCalledFunction();
                if (called_func->getName()=="write")
                     {
                     if (reg= CI->getArgOperand(2))
                     
           return true;
                      }
       else
         return false;
                             
  }
  }
};

static RegisterFIRegSelector X("onlyWriteSize", new _API6FIRegSelector());

}
