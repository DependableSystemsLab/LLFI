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
#include <map>
#include <set>
#include <string>
/**
 * This instruction selector only selects the API call functions as target
 */

using namespace llvm;
namespace llfi{
    class _API_WrongAPIInstSelector: public FIInstSelector{
        public:
            _API_WrongAPIInstSelector(){
                if(funcNamesTargetArgs.size() == 0){
                  funcNamesTargetArgs["fread"] = std::set<int>();
                  funcNamesTargetArgs["fwrite"]= std::set<int>();
                  funcNamesTargetArgs["fgetc"] = std::set<int>();
                  funcNamesTargetArgs["fopen"] = std::set<int>();
                  funcNamesTargetArgs["fwrite"].insert(3);
                  funcNamesTargetArgs["fread"].insert(3);
                  funcNamesTargetArgs["fgetc"].insert(2);
                  funcNamesTargetArgs["fopen"].insert(0);
                  funcNamesTargetArgs["fopen"].insert(1);
                }
            }

            static bool isTarget(CallInst* CI, Value* T){
              std::string func_name = CI->getCalledFunction()->getName();
              if(funcNamesTargetArgs.find(func_name) == funcNamesTargetArgs.end())
                return false;
              for(std::set<int>::iterator SI = funcNamesTargetArgs[func_name].begin(); SI != funcNamesTargetArgs[func_name].end(); SI++){
                if(T == CI->getArgOperand(*SI)) return true;
              }
              return false;
            }

        private:
            static std::map<std::string, std::set<int> > funcNamesTargetArgs;

        virtual bool isInstFITarget(Instruction* inst){
            if(isa<CallInst>(inst) == false)    return false;
            else{
                CallInst* CI = dyn_cast<CallInst>(inst);
                Function* called_func = CI->getCalledFunction();
                if(called_func == NULL) return false;
                std::string func_name = std::string(called_func->getName());
                if(funcNamesTargetArgs.find(func_name) != funcNamesTargetArgs.end())    return true;
                else return false;
            }
        } 
    };

    class _API_WrongAPIRegSelector: public FIRegSelector{
      private:
      virtual bool isRegofInstFITarget(Value *reg, Instruction *inst){
        if(isa<CallInst>(inst) == false)  return false;
        CallInst* CI = dyn_cast<CallInst>(inst);
        Function* called_func = CI->getCalledFunction();
        if(called_func == NULL) return false;
        if(_API_WrongAPIInstSelector::isTarget(CI, reg))  return true;
        else  return false;
      }
    };
    static RegisterFIInstSelector A("WrongAPI(API)", new _API_WrongAPIInstSelector());
    static RegisterFIRegSelector B("WrongAPI(API)", new _API_WrongAPIRegSelector());
}
