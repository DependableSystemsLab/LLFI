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
    class _Data_CorruptionInstSelector: public FIInstSelector{
    private:
        virtual bool isInstFITarget(Instruction* inst){
            if(isa<CallInst>(inst) == false)    return false;
            else{
                return true;
            }
        }
    public:
        virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
            info["failure_class"] = "Data";
            info["failure_mode"] = "DataCorruption";
            info["targets"] = "all-call-instructions";
            info["injector"] = "BitCorruptionInjector";
        }
    };
    static RegisterFIInstSelector A( "DataCorruption(Data)", new _Data_CorruptionInstSelector());
    static RegisterFIRegSelector B("DataCorruption(Data)", new FuncArgRegSelector(0));
}