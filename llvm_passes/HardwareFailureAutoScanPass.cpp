#define DEBUG_TYPE "HardwareFailureAutoScanPass"

#include "FICustomSelectorManager.h"
#include "Utils.h"
#include "FIInstSelectorManager.h"
#include "FIInstSelector.h"
#include "InstTypeFIInstSelector.h"
#include "FuncNameFIInstSelector.h"
#include "FIRegSelector.h"
#include "RegLocBasedFIRegSelector.h"

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"

#include <fstream>
#include <iostream>

using namespace llvm;
namespace llfi{
    static cl::opt< std::string > outputpath("hardwarescan_outputfilename",
        cl::desc("The path to store a list of applicable software failures"),
        cl::init("llfi.applicable.hardware.selectors.txt"));

    class HardwareFailureAutoScanPass: public ModulePass{
    private:
        std::ofstream selector_record_file;
    public:
        static char ID;
        HardwareFailureAutoScanPass():ModulePass(ID){}
        virtual bool runOnModule(Module &M){
            selector_record_file.open(std::string(outputpath).c_str(), std::ofstream::out);

            FICustomInstSelectorManager *im = FICustomInstSelectorManager::getCustomInstSelectorManager();
            FICustomRegSelectorManager *rm = FICustomRegSelectorManager::getCustomRegSelectorManager();
            std::set<std::string> all_hardware_inst_selector_names;
            im->getAllHardwareSelectors(all_hardware_inst_selector_names);
            all_hardware_inst_selector_names.insert(std::string("insttype"));
            all_hardware_inst_selector_names.insert(std::string("funcname"));

            std::set<std::string> all_hardware_reg_selector_names;
            rm->getAllHardwareSelectors(all_hardware_reg_selector_names);
            all_hardware_reg_selector_names.insert(std::string("regloc"));
            // errs()<<"get all soft failures\n";

            recordString(std::string("instSelMethod:"));
            for(std::set<std::string>::iterator name = all_hardware_inst_selector_names.begin();
                name != all_hardware_inst_selector_names.end(); name++){
                {
                    recordString(std::string("    - ") + *name);
                }
            }

            recordString(std::string("regSelMethod:"));
            for(std::set<std::string>::iterator name = all_hardware_reg_selector_names.begin();
                name != all_hardware_reg_selector_names.end(); name++){
                {
                    recordString(std::string("    - ") + *name);
                }
            }
            selector_record_file.close();
        }

        void recordString(std::string str){
            if(selector_record_file.is_open() == false){
                std::cerr<<"ERROR: can not open file to record applicable selectors: ";
                std::cerr<<outputpath<<"\n";
                selector_record_file.close();
                return;
            }
            selector_record_file<<str<<"\n";
            return;
        }
    };
    char HardwareFailureAutoScanPass::ID = 0;
    static RegisterPass<HardwareFailureAutoScanPass> 
        X("HardwareFailureAutoScanPass", "Automatic scanner of hardware failure modes (instruction selectors, reg selectors)", 
            false, false);
}