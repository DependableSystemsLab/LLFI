#include "llvm/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>

#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"

/**
 * This instruction selector only selects the API call functions as target
 */
using namespace llvm;

namespace llfi {
class _API_Incorrect_OutputInstSelector: public FIInstSelector {
private: 
  
  virtual bool isInstFITarget(Instruction *inst)

         {
                          if(isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                              
                 
                                            std::ofstream outf("Automation-config");
                                              outf << "APIIncorrectOutput" << "\n";
                                                outf.close();
                      
             
                                            std::ifstream inf("Automation-config");
                                              std::string strInput;
                                                getline(inf, strInput);
                                     
                                           if (strInput=="APIIncorrectOutput") 
                                                      {
                                                     std::cout<<strInput<<"\n";
                                                       std::cout<<"successful"<<"\n";
                                                        inf.close();
                                             
                                            return true;
                                                      }
                                                   
                                         }
                                }
                                            else
                                            return false;

                                 
          }   

                                                };

     
                    


static RegisterFIInstSelector X( "IncorrectOutput(API)", new _API_Incorrect_OutputInstSelector()); 
}
                                            




