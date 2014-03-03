#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the malloc as target
 */
using namespace llvm;
namespace llfi {
class _Res_LowMemoryInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if(called_func->getName()=="malloc")
                 {  std::cout<< "malloc Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "LowMemory" << "\n";
                outf.close();
 
                                            std::ofstream outf2("gui-config.txt");
                outf2 << "Resource LowMemory malloc MemoryConsumer" << "\n";
                outf2.close();   
                      
                      
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="LowMemory") 
           {
                   std::cout<<strInput<<"\n";
           std::cout<<"successful"<<"\n";
                  inf.close();

          }
           return true;
                 }
       else
         return false;
                                 }
 }
                                               };

static RegisterFIInstSelector X( "LowMemory(Res)", new _Res_LowMemoryInstSelector());
}
