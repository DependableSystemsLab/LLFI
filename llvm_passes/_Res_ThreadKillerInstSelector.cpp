#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the pthread_join functions as target
 */
using namespace llvm;
namespace llfi {
class _Res_ThreadKillerInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if((called_func->getName()=="pthread_create")||(called_func->getName()=="pthread_join"))
                 {  std::cout<< "thread was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "MemThreadKiller" << "\n";
                outf.close();
                      
                
                                            std::ofstream outf2("gui-config.txt");
                outf2 << "Resource ThreadKiller pthread_join/pthread_create ThreadKiller" << "\n";
                outf2.close();   


             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="MemThreadKiller") 
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

static RegisterFIInstSelector X( "ThreadKiller(Res)", new _Res_ThreadKillerInstSelector());
}
