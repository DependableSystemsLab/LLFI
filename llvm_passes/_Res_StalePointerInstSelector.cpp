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
class _Res_StalePointerInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
                                CallInst* CI=dyn_cast<CallInst>(inst);
                                Function* called_func=CI->getCalledFunction();
                                if( (called_func->getName()=="malloc") || (called_func->getName()=="calloc"))
                                   {  std::cout<< "malloc or calloc Call was found"<<"\n";
                                      std::ofstream outf("Automation-config");
                                      outf << "MEMStalePointer" << "\n";
                                      outf.close();
                      

                                      std::ofstream outf2("gui-config.txt");
                                      outf2 << "Resource StalePointer malloc/calloc BitFlip" << "\n";
                                      outf2.close();   
             
                                      std::ifstream inf("Automation-config");
                                      std::string strInput;
                                      getline(inf, strInput);
                                      if (strInput=="MEMStalePointer") 
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
      else
      return false;
 }
                                               };

static RegisterFIInstSelector X( "StalePointer(Res)", new _Res_StalePointerInstSelector());
}
