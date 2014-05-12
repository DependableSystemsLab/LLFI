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
class _Timing_HighFrequentEventInstSelector: public FIInstSelector {
private: 
  

  virtual bool isInstFITarget(Instruction *inst)

 {
        
                        if(isa<TerminatorInst>(inst))
                                 { 
                                   TerminatorInst* TI=dyn_cast<TerminatorInst>(inst);
                                    
                                          if(isa<ReturnInst>(TI))
                                            {
                                         std::cout<< "return was found"<<"\n";
                                            std::ofstream outf("Automation-config");
                                              outf << "HighFrequentEvent-on-RETURN" << "\n";
                                                outf.close();



                std::ifstream inf("Automation-config");
                std::string strInput;
                getline(inf, strInput);
           if (strInput=="HighFrequentEvent-on-RETURN")
           {

                std::ofstream outf2("gui-config.txt");
                outf2 << "Timing HighFrequentEvent IO-Call/Return CPUHogger" << "\n";
                outf2.close();  


                std::cout<<strInput<<"\n";
                std::cout<<"successful"<<"\n";
                inf.close();

           }

                                            }

                                 }

                 else  if(isa<CallInst>(inst))
                                 {
                                  CallInst* CI=dyn_cast<CallInst>(inst);
                                    Function* called_func=CI->getCalledFunction();
                                      if((called_func->getName()=="fclose")||(called_func->getName()=="fopen")||(called_func->getName()=="fread")||(called_func->getName()=="fwrite"))
                                           {  
                                         std::cout<< "I/O Call was found"<<"\n";
                                           std::ofstream outf2("Automation2-config");
                                             outf2 << "HighFrequentEvent-on-IO" << "\n";
                                              outf2.close();
                                                                        
             std::ifstream inf2("Automation2-config");
                 std::string strInput2;
                  getline(inf2, strInput2);
           if (strInput2=="HighFrequentEvent-on-IO")
           {

                std::ofstream outf2("gui-config.txt");
                outf2 << "Timing HighFrequentEvent IO-Call/Return CPUHogger" << "\n";
                outf2.close();  


                std::cout<<strInput2<<"\n";
                std::cout<<"successful"<<"\n";
                inf2.close();

                return true;
           }
                                          }
                                 }
  
       else
         return false;
                                
 }               
                                               };

static RegisterFIInstSelector X( "HighFrequentEvent(Timing)", new _Timing_HighFrequentEventInstSelector());
}
