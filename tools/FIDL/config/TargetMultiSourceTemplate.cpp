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
//fidl_2
        if (funcNamesTargetArgs.size() == 0) {
//fidl_3
        }
    }
    
    virtual void getCompileTimeInfo(std::map<std::string, std::string>& info) {
//fidl_4
        for (std::map<std::string, std::set<int> >::iterator MI = funcNamesTargetArgs.begin(); MI != funcNamesTargetArgs.end(); MI++) {
            info["targets"] += MI->first + "()/";
        }
        //remove the '/' at the end
        info["targets"] = info["targets"].substr(0, info["targets"].length() - 1);
//fidl_5
    }
    
    static bool isTarget(CallInst* CI, Value* T) {
        std::string func_name = CI->getCalledFunction()->getName();
//fidl_6
            if (*SI >= CI->getNumArgOperands()) {
                continue;
            } else if (T == CI->getArgOperand(*SI)) {
                return true; 
            }
        }
        return false;
    }
    
    private:
    static std::map<std::string, std::set<int> > funcNamesTargetArgs;
    
    virtual bool isInstFITarget(Instruction* inst) {
        if (!isa<CallInst>(inst)) {
            return false;
        }
        
        CallInst* CI = dyn_cast<CallInst>(inst);
        Function* called_func = CI->getCalledFunction();
        if (called_func == NULL) { 
            return false;
        }
        
        std::string func_name = std::string(called_func->getName());
//fidl_7
    }
    
    static bool isTargetLLFIIndex(Instruction* inst) {
//fidl_8
        if (numOfSpecInsts > 0) {
            long llfiindex = getLLFIIndexofInst(inst);
            for (int i = 0; i < numOfSpecInsts; i++) {  
                if (llfiindex == IndexOfSpecInsts[i]) { 
                    return true;
                }
            }
            return false;
        } else {
            return true;
        }
    }
    
    // does something in funcNamesTargetArgs matches partially with func_name?
    static std::map<std::string, std::set<int> >::iterator key_partially_matches(std::string func_name) {
        std::map<std::string, std::set<int> >::iterator SI;
        for (SI = funcNamesTargetArgs.begin(); SI != funcNamesTargetArgs.end(); SI++) {
            if (func_name.find(SI->first) != std::string::npos) {   
                break;
            }
        }
        return SI;
    }
};

//fidl_9
    private:
    virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) {
        if (isa<CallInst>(inst) == false) {
            return false;
        }
        CallInst* CI = dyn_cast<CallInst>(inst);
        Function* called_func = CI->getCalledFunction();
        if (called_func == NULL) {
            return false;
        }
//fidl_10
        } else { 
            return false;
        }
    }
};

