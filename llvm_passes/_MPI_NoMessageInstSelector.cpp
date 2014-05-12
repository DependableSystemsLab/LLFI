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
class _MPI_NoMessageInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if ((called_func->getName()=="recv")||(called_func->getName()=="send"))
                 {  std::cout<< " Send or receive Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "MPINoMessage" << "\n";
                outf.close();
                      
                 std::ofstream outf2("gui-config.txt");
                outf2 << "MPI NoMessage Send/Receive Bitflip" << "\n";
                outf2.close();    
 
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="MPINoMessage") 
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

static RegisterFIInstSelector X( "NoMessage(MPI)", new _MPI_NoMessageInstSelector());
}
