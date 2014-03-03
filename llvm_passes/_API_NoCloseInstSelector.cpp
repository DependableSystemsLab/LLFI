#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
/**
 * This instruction selector only selects the API call functions as target
 */
using namespace llvm;
namespace llfi {
class _API_NoCloseInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if(called_func->getName()=="fclose")
                 {  std::cout<< "close Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "APINoClose" << "\n";
                outf.close();
                    
         std::ofstream outf2("gui-config.gui");
                outf2 << "API NoClose fclose BitFlip" << "\n";
                outf2.close();    
   
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
          // if (strInput=="APINoClose") 
          // {
         //          std::cout<<strInput<<"\n";
         //  std::cout<<"successful"<<"\n";
                  inf.close();

          // }
           return true;
                 }
       else
         return false;
                                 }
 }
                                               };

static RegisterFIInstSelector X( "NoClose(API)", new _API_NoCloseInstSelector());
}
