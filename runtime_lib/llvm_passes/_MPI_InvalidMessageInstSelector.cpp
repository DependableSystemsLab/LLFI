

#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>

/**
 * This instruction selector only selects the mpi call functions as target
 */
using namespace llvm;
namespace llfi {
class _MPI_InvalidMessageInstSelector: public FIInstSelector {
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
                outf << "MPIInvalidMessage" << "\n";
                outf.close();
                      
                 std::ofstream outf2("gui-config.txt");
                outf2 << "MPI InvalidMessage Send/Receive Bitflip" << "\n";
                outf2.close();    
 
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="MPIInvalidMessage") 
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

static RegisterFIInstSelector X( "InvalidMessage(MPI)", new _MPI_InvalidMessageInstSelector());
}
