
#define DEBUG_TYPE "AutoScan_Pass"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"
#include <fstream>
#include <iostream>
using namespace llvm;

      namespace {
      struct AutoScan_Pass : public FunctionPass
    {
    static char ID; // Pass identification, replacement for typeid
    AutoScan_Pass() : FunctionPass(ID) {}

       virtual bool runOnFunction(Function &F)
      { 

	//std::ofstream CFL("Custom-Failure-List.txt");
        //std::ofstream CFL2("Custom-Failure-List2.txt");
	//if (CFL.is_open())
	//{
        //CFL.is_open();
    
        std::ofstream CFL;
        CFL.open ("Custom-Failure-List.txt",std::ios::out | std::ios::app); 
       

                for( Function::iterator b = F.begin() ; b!= F.end() ; ++b)
                {
                      BasicBlock* BB = dyn_cast<BasicBlock>(&*b);
                      for(BasicBlock::iterator II = BB->begin() , IE=BB->end(); II != IE; II ++)
                      {
                             Instruction* inst = &*II;
                            


                            if(isa<TerminatorInst>(inst))
                             { 
                                 TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
		                         if((isa<ReturnInst>(TI))&& (TI->getParent()->getParent()->getName() != "main"))
		                           {
		                                                    CFL<< "IncorrectOutput(API)\n"; 
								    CFL<< "NoOutput(API)\n"; 
								    CFL<< "CPUHog(Res)\n"; 
                                                                    CFL<< "NoOutput(Data)\n"; 
                                                                    CFL<< "IncorrectOutput(Data)\n";
                                                                    CFL<< "HighFrequentEvent(Timing)\n";
                                                                    	errs()<< " this is return related failures" <<"\n";      

                                           }
                                 
                             }   

   
                            if(isa<CallInst>(inst))
                             { 
	                           CallInst* CI=dyn_cast<CallInst>(inst);
	                           Function* called_func=CI->getCalledFunction();
	                                 if((called_func->getName()=="fread")||(called_func->getName()=="fwrite"))
	                                 { 

					
							 
								    CFL<< "BufferOverflow(API)\n";
								    CFL<< "BufferUnderflow(API)\n";
								    CFL<< "WrongSavedAddress(I/O)\n";   
								    CFL<< "WrongSavedFormat(I/O)\n"; 
								    CFL<< "WrongRetrievedAddress(I/O)\n"; 
								    CFL<< "WrongRetrievedFormat(I/O)\n"; 
								    CFL<< "WrongPointer(Data)\n"; 
                                                                    CFL<< "WrongAPI(API)\n"; 
                                                                    CFL<< "HighFrequentEvent(Timing)\n";
                                                                    CFL<< "DataCorruption(Data)\n";
									errs()<< " this is read.write related failures" <<"\n";
								   
									                           
					  }
			              else if(called_func->getName()=="fopen")
			                  { 
					   		
								    CFL<< "NoOpen(API)\n";
								    CFL<< "InappropriateClose(API)\n";
								    CFL<< "WrongMode(API)\n";   
								    	errs()<< " this is open related failures" <<"\n";
								    
								                                                                                                        
			                      
			                  }
			               
			              else if(called_func->getName()=="fclose")
			                  { 
			                   		
								    CFL<< "NoClose(API)\n";
								    	errs()<< " this is close related failure" <<"\n";
								
								                                                                   
			                  }

			              else if((called_func->getName()=="malloc")||(called_func->getName()=="calloc"))
			                  { 
                             
							            CFL<< "MemoryExhaustion(Res)\n";
								    CFL<< "LowMemory(Res)\n";
								    CFL<< "StalePointer(Res)\n";   
								    CFL<< "InvalidPointer(Res)\n"; 
                                                                    CFL<< "UnderAccumulator(Res)\n";  
								    CFL<< "BufOverflowMalloc(Data)\n"; 
								   	errs()<< " this is malloc related failures" <<"\n";
								   
								                                                               
                                           }


					else if ((called_func->getName()=="llvm.memcpy.p0i8.p0i8.i64")||(called_func->getName()=="llvm.memmove.p0i8.p0i8.i64"))
			                  { 
                             
							            CFL<< "WrongDestination(Data)\n";
								    CFL<< "WrongSource(Data)\n";
								    CFL<< "BufOverflowMemmove(Data)\n"; 
								    	errs()<< " this is memcpy related failures "<<"\n";
								 
					  }


					else if(called_func->getName()=="free")
			                  { 
                             
							
								    CFL<< "MemoryLeak(Res)\n";
								    	errs()<< " this is free related failure" <<"\n";
								    
					  }


					else if((called_func->getName()=="send")||(called_func->getName()=="recv"))
			                  { 
                             
								    CFL<< "NoMessage(MPI)\n";
								    CFL<< "InvalidMessage(MPI)\n";
								    CFL<< "NoAck(MPI)\n";   
								    CFL<< "NoDrain(MPI)\n"; 
                                                                    CFL<< "InvalidSender(MPI)\n";  
								    CFL<< "PacketStorm(MPI)\n"; 
								   	errs()<< " this is malloc related failures" <<"\n";
								                                                                
                                           }


					else if((called_func->getName()=="pthread_create")||(called_func->getName()=="pthread_join"))
			                  { 
                             
								    CFL<< "DeadLock(Res)\n";
								    CFL<< "ThreadKiller(Res)\n";
								      	errs()<< " this is pthread related failures" <<"\n";
								                                                                  
                                          }


					else if(called_func->getName()=="pthread_mutex_lock")
			                  { 
                             
								    CFL<< "RaceCondition(Timing)\n";
								        errs()<< " this is pthread related failures" <<"\n";
								                                                                
                                          
                                                                                   
                                       	  }
    
                                 }

                         }
           
		      
	          } 
		      
		        
         
		  
               
	  CFL.close();
        //  CFL2.close();
	 /* }
	  else 
	  errs()<< " unable to open the files" <<"\n";*/
       return false;
      }
    };
  }
char AutoScan_Pass::ID = 0;
static RegisterPass<AutoScan_Pass> X("AutoScan_Pass", "Automatic scanner of failure modes", false, false);


