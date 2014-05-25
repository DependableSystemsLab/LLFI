#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the pthread_join functions as target
 */
using namespace llvm;
namespace llfi {
class _Res_DeadLockInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if ((called_func->getName()=="pthread_join")||(called_func->getName()=="pthread_create"))
                 {  std::cout<< "pthread_join was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "MemDeadLock" << "\n";
                outf.close();


                                            std::ofstream outf2("gui-config.txt");
                outf2 << "Resource DeadLock pthread_join DeadLocker" << "\n";
                outf2.close();   
                      
                      
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="MemDeadLock") 
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

static RegisterFIInstSelector X( "DeadLock(Res)", new _Res_DeadLockInstSelector());
}
