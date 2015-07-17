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
namespace llfi{
         // probe 0  
    //class _API_BufferUnderflowInstSelector: public FIInstSelector{
        public:
          // probe 1
           // _API_BufferUnderflowInstSelector(){
         // probe 2
             //   funcNames.insert(std::string("fread"));
             //   funcNames.insert(std::string("fwrite"));
            }
            virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
          // probe 3
               // info["failure_class"] = "API";
               // info["failure_mode"] = "BufferUnderflow";
               // info["targets"] = "fread()/fwrite()";
               // info["injector"] = "ChangeValueInjector";
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
                if(funcNames.find(func_name) != funcNames.end())  
               { 
             // probe 5
             // probe 6
                long llfiindex = getLLFIIndexofInst(inst);
                 for (int i=0; i<numOfSpecInsts; i++)
                 {  
                  if (llfiindex+1==IndexOfSpecInsts[i])
                   { std::cout<< "Special Instruction Index is:"<<llfiindex+1<<"\n"; }
                 }
  return true;}
                else return false;
            }
        }
    };
    // probe 4
    //static RegisterFIInstSelector A( "BufferUnderflow(API)", new _API_BufferUnderflowInstSelector());
    //static RegisterFIRegSelector B("BufferUnderflow(API)", new FuncArgRegSelector(2));
}
