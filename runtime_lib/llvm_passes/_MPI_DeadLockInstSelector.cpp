

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
class _MPI_DeadLockInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
              Function* called_func=CI->getCalledFunction();
                             
                 if ((called_func->getName()=="recv")||(called_func->getName()=="send"))
                 {  std::cout<< " Send to or receive from Call was found"<<"\n";
                 
                std::ofstream outf("Automation-config");
                outf << "MPIDeadLock" << "\n";
                outf.close();
                      
                 std::ofstream outf2("gui-config.txt");
                outf2 << "MPI DeadLock sendto/recvfrom Bitflip" << "\n";
                outf2.close();    
 
             
             std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
           if (strInput=="MPIDeadLock") 
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

static RegisterFIInstSelector X( "DeadLock(MPI)", new _MPI_DeadLockInstSelector());
}
