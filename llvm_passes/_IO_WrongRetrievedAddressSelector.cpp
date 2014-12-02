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
    class _IO_WrongRetrievedAddressInstSelector: public FIInstSelector{
        public:
            _IO_WrongRetrievedAddressInstSelector(){
                funcNames.insert(std::string("fread"));
                funcNames.insert(std::string("fwrite"));
            }
            virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
                info["failure_class"] = "I/O";
                info["failure_mode"] = "WrongRetrievedAddress";
                for(std::set<std::string>::iterator SI = funcNames.begin();
                  SI != funcNames.end(); SI++){
                  info["targets"] += *SI + "()/";
                }
                //remove the '/' at the end
                info["targets"] = info["targets"].substr(0, info["targets"].length()-1);
                info["injector"] = "BitCorruptionInjector";
            }

        private:
            std::set<std::string> funcNames;

        virtual bool isInstFITarget(Instruction* inst){
            if(isa<CallInst>(inst) == false)    return false;
            else{
                CallInst* CI = dyn_cast<CallInst>(inst);
                Function* called_func = CI->getCalledFunction();
                if(called_func == NULL) return false;
                std::string func_name = std::string(called_func->getName());
                if(funcNames.find(func_name) != funcNames.end())    return true;
                else return false;
            }
        }
    };

    class _IO_WrongRetrevedAddressRegSelector: public FIRegSelector{
      private:
      virtual bool isRegofInstFITarget(Value *reg, Instruction *inst){
        if(isa<CallInst>(inst) == false)  return false;
        CallInst* CI = dyn_cast<CallInst>(inst);
        Function* called_func = CI->getCalledFunction();
        if(called_func == NULL) return false;
        if(called_func->getName() == "fwrite"){
          return reg == CI->getArgOperand(0);
        }else if(called_func->getName() == "fread"){
          return reg == CI->getArgOperand(3);
        }
        else  return false;
      }
    };
    static RegisterFIInstSelector A("WrongRetrievedAddress(IO)", new _IO_WrongRetrievedAddressInstSelector());
    static RegisterFIRegSelector B("WrongRetrievedAddress(IO)", new _IO_WrongRetrevedAddressRegSelector());
}