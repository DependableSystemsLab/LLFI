

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
class _Timing_RaceConditionInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if(called_func->getName()=="pthread_mutex_lock")
                 {  std::cout<< "pthread_mutex_lock was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "RaceCondition" << "\n";
                outf.close();
                      
                
                                            std::ofstream outf2("gui-config.txt");
                outf2 << "Timing RaceCondition pthread_mutex_lock RaceConditionCreator" << "\n";
                outf2.close();   


             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="RaceCondition") 
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

static RegisterFIInstSelector X( "RaceCondition(Timing)", new _Timing_RaceConditionInstSelector());
}
