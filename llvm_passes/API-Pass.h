#define DEBUG_TYPE "API_Pass"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"
using namespace llvm;

  int open_count=0;
  int close_count=0;
  int read_count=0;
  int write_count=0;
   int num_operand_open;
   int num_operand_close;
   int num_operand_read;
   int num_operand_write;
     namespace {
     //class perturbData {
    // public :  perturbData();
     // };
  struct API_Pass : public FunctionPass
        {
    static char ID; // Pass identification, replacement for typeid
    API_Pass() : FunctionPass(ID) {}

       virtual bool runOnFunction(Function &F)
           { 
                for( Function::iterator b = F.begin() ; b!= F.end() ; ++b)
                {
                      BasicBlock* BB = dyn_cast<BasicBlock>(&*b);
                      
                           for(BasicBlock::iterator II = BB->begin() , IE=BB->end(); II != IE; II ++)
                           {
                             Instruction* inst = &*II;

                                 if(isa<CallInst>(inst))
                                 { 
                                   CallInst* CI=dyn_cast<CallInst>(inst);
                                     Function* called_func=CI->getCalledFunction();
                                      if(called_func->getName()=="open")
                                          { ++open_count;
		                            num_operand_open = CI->getNumArgOperands() ;
                                             Value * operand1=CI->getArgOperand(0) ;
                                               errs()<<" The address of first oprand is :" << *operand1<<"\n";
                                            //  Value * perturboperand= dyn_cast<perturbData>(&*operand1)
                                             //   CI->setArgOperand(0,*perturboperand);
                                             //errs()<<" The new address of first oprand is :" << CI->getArgOperand(0)<<"\n";
                                              // errs()<< " The address of second oprand is :" <<CI->getArgOperand(1)<<"\n";
					  }
                                      if(called_func->getName()=="close")
                                          { ++close_count;
		                            num_operand_close = CI->getNumArgOperands() ;
                                             
                                              
                                          }
                                       
                                      if(called_func->getName()=="read")
                                          { ++read_count;
		                            num_operand_read= CI->getNumArgOperands() ;
                                             
                                               
                                          }
                                       if(called_func->getName()=="write")
                                          { ++write_count;
		                            num_operand_write = CI->getNumArgOperands() ;
                                             
                                               
                                       	  }      
                                 } 
                           }
                      
                }

     errs()<< " The number of open call(s) is :" << open_count  <<"\n";
       errs()<< " The number of operand(s) of open function is :" <<num_operand_open<< "\n";
     errs()<< " The number of close call(s) is :" << close_count  <<"\n";
       errs()<< " The number of operand(s) of close function is :" <<num_operand_close<< "\n";
     errs()<< " The number of read call(s) is :" << read_count  <<"\n";
       errs()<< " The number of operand(s) of read function is:" <<num_operand_read<< "\n";
     errs()<< " The number of write call(s) is :" << write_count  <<"\n";
       errs()<< " The number of operand(s) of write function is :" <<num_operand_write<< "\n";
         return false; 
          }
   
      };
 
          }
char API_Pass::ID = 0;
static RegisterPass<API_Pass> X("API_Pass", "API Function Calls", false, false);









