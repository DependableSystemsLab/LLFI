#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"

/**
 * This instruction selector only selects the Memory allocation functions as target
 */
using namespace llvm;
namespace llfi {
class _Data_CorruptionInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
       

         if(isa<CallInst>(inst))
                                 {
         CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                errs()<<called_func->getName()<<"\n";
                     std::ofstream outf("Automation-config");
                        outf << "DataCorruption" << "\n";
                         outf.close();  
  std::ofstream outf2("gui-config.txt");
                outf2 << "Data DataCorruption all-called-instructions Bitflip" << "\n";
                outf2.close();    
           return true;
                 }
       else
         return false;



                                 }
// }
                                               };

static RegisterFIInstSelector X( "DataCorruption(Data)", new _Data_CorruptionInstSelector());
}
