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
class _API_BufferOverflowInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if((called_func->getName()=="fread")||(called_func->getName()=="fwrite"))
                 {  std::cout<< "read or write Call was found"<<"\n";
                 //   std::cout<< "function name is :"<<called_func->getName()<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "APIBufferOverflow" << "\n";
                outf.close();
                      
                std::ofstream outf2("gui-config.txt");
                outf2 << "API BufferOverflow fread/fwrite IncValue" << "\n";
                outf2.close();    
 
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="APIBufferOverflow") 
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

static RegisterFIInstSelector X( "BufferOverflow(API)", new _API_BufferOverflowInstSelector());
}
