#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the API call functions as target
 */
using namespace llvm;
namespace llfi {
class _API_NoOpenInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if(called_func->getName()=="fopen")
                 {  std::cout<< "open Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "APINoOpen" << "\n";
                outf.close();
                      
               std::ofstream outf2("gui-config.txt");
                outf2 << "API NoOpen fopen BitFlip" << "\n";
                outf2.close();    
 

             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="APINoOpen") 
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

static RegisterFIInstSelector X( "NoOpen(API)", new _API_NoOpenInstSelector());
}
