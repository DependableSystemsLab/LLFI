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
class _IO_WrongRFormatInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if(called_func->getName()=="fread")
                 {  std::cout<< "read Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "APIWrongFormat" << "\n";
                outf.close();
                      
              std::ofstream outf2("gui-config.txt");
                outf2 << "I/O WrongRetrievedFormat fread FormatModifier" << "\n";
                outf2.close();   

             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="APIWrongFormat") 
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

static RegisterFIInstSelector X( "WrongRetrievedFormat(I/O)", new _IO_WrongRFormatInstSelector());
}
