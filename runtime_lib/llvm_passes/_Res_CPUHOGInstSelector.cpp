#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/CFG.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/GraphTraits.h"

/**
 * This instruction selector only selects the API call functions as target
 */
using namespace llvm;
int count=0;
namespace llfi {
class _Res_CPUHOGInstSelector: public FIInstSelector {
private: 
  
  virtual bool isInstFITarget(Instruction *inst)

         {
                          if(isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                              
                 
                                            std::ofstream outf("Automation-config");
                                              outf << "CPUHogTarget" << "\n";
                                                outf.close();
                   
                                            std::ofstream outf2("gui-config.txt");
                outf2 << "Resource CPUHog return CPUHogger" << "\n";
                outf2.close();   
                      
             
                                            std::ifstream inf("Automation-config");
                                              std::string strInput;
                                                getline(inf, strInput);
                                     
                                           if (strInput=="CPUHogTarget") 
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

     
                    


static RegisterFIInstSelector X( "CPUHog(Res)", new _Res_CPUHOGInstSelector()); 
}
                                            




