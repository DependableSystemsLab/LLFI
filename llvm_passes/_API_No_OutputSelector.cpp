#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include "_SoftwareFaultRegSelectors.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>

/**
 * This instruction selector only selects the API call functions as target
 */

using namespace llvm;
namespace llfi{
    class _API_No_OutputInstSelector: public FIInstSelector{
        private:
        virtual bool isInstFITarget(Instruction* inst){
            return isa<ReturnInst>(inst);
        } 
    };
    static RegisterFIInstSelector A( "NoOutput(API)", new _API_No_OutputInstSelector());
    static RegisterFIRegSelector B("NoOutput(API)", new RetValRegSelector());
}