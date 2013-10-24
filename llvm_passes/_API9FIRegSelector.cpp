#include "llvm/Value.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"


namespace llfi {

/**
 * This register selector only selects the second operand of open function as target
 */
class _API9FIRegSelector: public FIRegSelector {
 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {
    

         if(isa<CallInst>(inst))
                                {
             CallInst* CI=dyn_cast<CallInst>(inst);
         
              Function* called_func=CI->getCalledFunction();
                if (called_func->getName()=="open")
                     {
                     if (reg= CI->getArgOperand(1))
                     
           return true;
                      }
       else
         return false;
                             
  }
  }
};

static RegisterFIRegSelector X("onlyOpenMode", new _API9FIRegSelector());

}
