#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"

#include "Utils.h"
#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include "_SoftwareFaultRegSelectors.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace llvm;
namespace llfi {
//fidl_1
    public:
    virtual void getCompileTimeInfo(std::map<std::string, std::string>& info) {
//fidl_2
    }
    private:
    virtual bool isInstFITarget(Instruction* inst) {
//fidl_3
    }
    
    static bool isTargetLLFIIndex(Instruction* inst) {
//fidl_4
        if (n > 0) {
            long llfiindex = getLLFIIndexofInst(inst);
            for (int i = 0; i < n; i++) {  
                if (llfiindex == targeted_indices[i]) { 
                    return true;
                }
            }
            return false;
        } else {
            return true;
        }
    }
};

