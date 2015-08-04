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
#include <set>
#include <string>

/**
 * This instruction selector only selects the API call functions as target
 */

using namespace llvm;
namespace llfi {
//fidl_1
    public:
//fidl_2
//fidl_3
    }
    
    virtual void getCompileTimeInfo(std::map<std::string, std::string>& info) {
//fidl_4
        for(std::set<std::string>::iterator SI = funcNames.begin(); SI != funcNames.end(); SI++){
            info["targets"] += *SI + "()/";
        }
        //remove the '/' at the end
        info["targets"] = info["targets"].substr(0, info["targets"].length() - 1);
//fidl_5
    }

    private:
    std::set<std::string> funcNames;

    virtual bool isInstFITarget(Instruction* inst) {
        if (isa<CallInst>(inst) == false) {
            return false;
        } else {
            CallInst* CI = dyn_cast<CallInst>(inst);
            Function* called_func = CI->getCalledFunction();
            if (called_func == NULL) {
                return false;
            }
            std::string func_name = std::string(called_func->getName());
            if (funcNames.find(func_name) != funcNames.end()) { 
//fidl_6
                long llfiindex = getLLFIIndexofInst(inst);
                for (int i = 0; i < numOfSpecInsts; i++) {  
                    if (llfiindex + 1 == IndexOfSpecInsts[i]) {
                        std::cout << "Special Instruction Index is:" << llfiindex + 1 << "\n"; 
                    }
                }
                return true;
            } else {
                return false;
            }
        }
    }
};

