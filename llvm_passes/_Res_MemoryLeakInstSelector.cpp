#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the memory deallocation call functions as target
 */
using namespace llvm;
namespace llfi {
class _Res_MemoryLeakInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
        {
                   CallInst* CI=dyn_cast<CallInst>(inst);
                    Function* called_func=CI->getCalledFunction();
                      if(called_func->getName()=="free")
                      {  
                          std::cout<< "free Call was found"<<"\n";
                          std::ofstream outf("Automation-config");
                          outf << "MemMemoryLeak" << "\n";
                          outf.close();
                      
                          std::ofstream outf2("gui-config.txt");
                          outf2 << "Resource MemoryLeak free FakeDe-allocator" << "\n";
                          outf2.close();   
             
                          std::ifstream inf("Automation-config");
                          std::string strInput;
                          getline(inf, strInput);
                       
                     return true;
                      }
                     else
                     return false;
                                 
      //return true;
      }
      else
      return false;
 }
                                               };

static RegisterFIInstSelector X( "MemoryLeak(Res)", new _Res_MemoryLeakInstSelector());
}
