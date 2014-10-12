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
    class _Timing_HighFrequentEventInstSelector: public FIInstSelector{
        public:
            _Timing_HighFrequentEventInstSelector(){
                funcNames.insert(std::string("fread"));
                funcNames.insert(std::string("fopen"));
                funcNames.insert(std::string("fwrite"));
            }

        private:
            std::set<std::string> funcNames;

        virtual bool isInstFITarget(Instruction* inst){
            if(isa<CallInst>(inst)){
                CallInst* CI = dyn_cast<CallInst>(inst);
                Function* called_func = CI->getCalledFunction();
                if(called_func == NULL) return false;
                std::string func_name = std::string(called_func->getName());
                if(funcNames.find(func_name) != funcNames.end())    return true;
                else return false;
            }else if(isa<ReturnInst>(inst)){
              return true;
            }
            else  return false;
        } 
    };

    class _Timing_HighFrequentEventRegSelector: public FIRegSelector{
      private:
      virtual bool isRegofInstFITarget(Value *reg, Instruction *inst){
        if(isa<CallInst>(inst)){
          CallInst* CI = dyn_cast<CallInst>(inst);
          Function* called_func = CI->getCalledFunction();
          if(called_func == NULL) return false;
          return reg == CI;
        }else if(isa<ReturnInst>(inst)){
          ReturnInst* RI = dyn_cast<ReturnInst>(inst);
          return reg == RI->getReturnValue();
        }
        else  return false;
      }
    };
    static RegisterFIInstSelector A("HighFrequentEvent(Timing)", new _Timing_HighFrequentEventInstSelector());
    static RegisterFIRegSelector B("HighFrequentEvent(Timing)", new _Timing_HighFrequentEventRegSelector());
}