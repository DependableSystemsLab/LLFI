
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"
#include "FIInstSelector.h"
#include "Utils.h" 
#include "FICustomSelectorManager.h"
#include "_SoftwareFaultRegSelectors.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace llvm;
namespace llfi{
// mark 1
public:
// mark 2
if(funcNamesTargetArgs.size() == 0){
// mark 3
}
}
virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
// mark 4
for(std::map<std::string, std::set<int> >::iterator MI = funcNamesTargetArgs.begin();
MI != funcNamesTargetArgs.end(); MI++){
info["targets"] += MI->first + "()/";
}
//remove the '/' at the end
info["targets"] = info["targets"].substr(0, info["targets"].length()-1);
// mark 5
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
if(isa<CallInst>(inst) == false) return false;
else{
CallInst* CI = dyn_cast<CallInst>(inst);
Function* called_func = CI->getCalledFunction();
if(called_func == NULL) return false;
std::string func_name = std::string(called_func->getName());
if(funcNamesTargetArgs.find(func_name) != funcNamesTargetArgs.end())
//**
              { 
//mark 6
//mark 7
                long llfiindex = getLLFIIndexofInst(inst);
                 for (int i=0; i<numOfTainted; i++)
                 {  
                  if (llfiindex+1==IndexOfTainted[i])
                   { std::cout<< "Tainted Index is:"<<llfiindex+1<<"\n"; }
                 }
                     return true;}
//** return true;


else return false;
}
}
};
// mark 8


// mark 9
private:
virtual bool isRegofInstFITarget(Value *reg, Instruction *inst){
if(isa<CallInst>(inst) == false) return false;
CallInst* CI = dyn_cast<CallInst>(inst);
Function* called_func = CI->getCalledFunction();
if(called_func == NULL) return false;
//mark 10
else return false;}
 };
//mark 11
//mark 12

