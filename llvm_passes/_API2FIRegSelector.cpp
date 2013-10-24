#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"


namespace llfi {

/**
 * This register selector only selects the first operand of close function as target
 */
class _API2FIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {
    

         if(isa<CallInst>(inst))
                                {
             CallInst* CI=dyn_cast<CallInst>(inst);
         
              Function* called_func=CI->getCalledFunction();
                if (called_func->getName()=="close")
                     {
                     if (reg= CI->getArgOperand(0))
                     
           return true;
                      }
       else
         return false;
                             
  }
  }
};

static RegisterFIRegSelector X("onlyCloseid", new _API2FIRegSelector());

}
