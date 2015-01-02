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

#include <set>
#include <string>

/**
 * This instruction selector only selects the API call functions as target
 */

using namespace llvm;
namespace llfi{
    class _API_WrongModeInstSelector: public SoftwareFIInstSelector{
    private:
        virtual bool isInstFITarget(Instruction* inst){
            if(isa<CallInst>(inst) == false)    return false;
            else{
                CallInst* CI = dyn_cast<CallInst>(inst);
                Function* called_func = CI->getCalledFunction();
                if(called_func == NULL) return false;
                if(called_func->getName() == "fopen")    return true;
                else return false;
            }
        }
    public:
        virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
            info["failure_class"] = "API";
            info["failure_mode"] = "WrongMode";
            info["targets"] = "fopen()";
            info["injector"] = "BitCorruptionInjector";
        }
    };
    static RegisterFIInstSelector A( "WrongMode(API)", new _API_WrongModeInstSelector());
    static RegisterFIRegSelector B("WrongMode(API)", new FuncArgRegSelector(1));
}
