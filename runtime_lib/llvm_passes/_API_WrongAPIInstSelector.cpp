#include "llvm/IR/Instructions.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include "llvm/IR/Instructions.h"



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
using namespace std;
using namespace llvm;

namespace llfi {
class _API_WrongAPIInstSelector: public FIInstSelector {
private: 
  
  virtual bool isInstFITarget(Instruction *inst)

    {    
               
        std::string line;
	string funcName[10];
	int   ArgPosNumber[10];
	std::ifstream inFile;
	inFile.open ("API-Config.txt");
	int i = 0;
    
    
	while(getline(inFile, line))

	{
                 //std::cout << line << "\n";
     		std::stringstream dosString;
		dosString<<line;
		dosString>> funcName[i]>>ArgPosNumber[i];
                i++;
	}

	  
    
         if(isa<CallInst>(inst))
                                 {
          CallInst* CI=dyn_cast<CallInst>(inst);
          Function* called_func=CI->getCalledFunction();                 
          for (int j = 0;  j< i; j++)
	    {
	    if (funcName[j].c_str()==called_func->getName())    
                           {       
                             std::cout<< "API Call was found"<<"\n";
                                std::ofstream outf("Automation-config");
                                   outf << "APIWrongAPI" << "\n";
                                      outf.close();

  std::ofstream outf2("gui-config.txt");
                outf2 << "API WrongAPI APIFunctions BitFlip" << "\n";
                outf2.close();    
                                                                                                       
                          std::cout<<"target is :"<<funcName[j]<<"\n";
                            
                            }
                                                                
           }
            }     

        std::ifstream inf("Automation-config");
                 std::string strInput;
                  getline(inf, strInput);
             if (strInput=="APIWrongAPI") 
                {
                  inf.close();
                  return true;
                }
                   else
                      return false;
                            
                              }  

                                        
         };
                    


static RegisterFIInstSelector X( "WrongAPI(API)", new _API_WrongAPIInstSelector()); 
}
                                            




