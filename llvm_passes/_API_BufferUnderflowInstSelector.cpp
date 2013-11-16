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
class _API_BufferUnderflowInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if((called_func->getName()=="fread")||(called_func->getName()=="fwrite"))
                 {  std::cout<< "read or write Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "APIBufferUnderflow" << "\n";
                outf.close();
                      
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="APIBufferUnderflow") 
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

static RegisterFIInstSelector X( "BufferUnderflow(API)", new _API_BufferUnderflowInstSelector());
}
