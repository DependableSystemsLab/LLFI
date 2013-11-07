#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"

/**
 * This instruction selector only selects the API call functions as target
 */
using namespace llvm;
namespace llfi {
class WriteCallInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                 if (called_func->getName()=="fwrite")
                 {  std::cout<< "write Call was found"<<"\n"; 
        
           return true;
                 }
       else
         return false;
                                 }
 }
                                               };

static RegisterFIInstSelector X( "onlyWriteCalls", new WriteCallInstSelector());
}
