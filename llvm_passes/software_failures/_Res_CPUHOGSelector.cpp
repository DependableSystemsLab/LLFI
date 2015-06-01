#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"

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
    class _Res_CPUHOGInstSelector: public SoftwareFIInstSelector{
    private:
        virtual bool isInstFITarget(Instruction* inst){
            return isa<ReturnInst>(inst);
        }
    public:
        virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
            info["failure_class"] = "Resource";
            info["failure_mode"] = "CPUHog";
            info["targets"] = "return";
            info["injector"] = "SleepInjector";
        }
    };
    static RegisterFIInstSelector A( "CPUHog(Res)", new _Res_CPUHOGInstSelector());
    static RegisterFIRegSelector B("CPUHog(Res)", new RetValRegSelector());
}