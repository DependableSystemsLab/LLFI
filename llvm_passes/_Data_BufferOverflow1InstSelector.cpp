#include "llvm/IR/Instructions.h"
#include <fstream>
#include <iostream>
#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include "llvm/IR/Intrinsics.h"
 
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
class _Data_BufferOverflow1InstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                //errs()<<called_func->getName()<<"\n";
                 if ((called_func->getName()=="malloc")||(called_func->getName()=="calloc"))
                 { 
                       std::ofstream outf("Automation-config");
                        outf << "MemBufOverflow1" << "\n";
                         outf.close();
                std::ofstream outf2("gui-config.txt");
                outf2 << "Data BufferOverflow malloc/calloc DecValue" << "\n";
                outf2.close();    
        
           return true;
                 }
       else
         return false;
                                 }
 }
                                               };

static RegisterFIInstSelector X( "BufOverflowMalloc(Data)", new _Data_BufferOverflow1InstSelector());
}
