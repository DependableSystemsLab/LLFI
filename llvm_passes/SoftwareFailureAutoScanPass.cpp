#define DEBUG_TYPE "SoftwareFailureAutoScanPass"

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
    static cl::opt< std::string > outputpath("softwarescan_outputfilename",
        cl::desc("The path to store a list of applicable software failures"),
        cl::init("llfi.applicable.software.failures.txt"));

    class SoftwareFailureAutoScanPass: public ModulePass{
    private:
        std::ofstream selector_record_file;
    public:
        static char ID;
        SoftwareFailureAutoScanPass():ModulePass(ID){}
        virtual bool runOnModule(Module &M){
            selector_record_file.open(std::string(outputpath).c_str(), std::ofstream::out);

            FICustomInstSelectorManager *im = FICustomInstSelectorManager::getCustomInstSelectorManager();
            FICustomRegSelectorManager *rm = FICustomRegSelectorManager::getCustomRegSelectorManager();
            std::set<std::string> all_software_failure_names;
            im->getAllSoftwareSelectors(all_software_failure_names);
            // errs()<<"get all soft failures\n";
            for(std::set<std::string>::iterator name = all_software_failure_names.begin();
                name != all_software_failure_names.end(); name++){
                // errs()<<"# start on: "<<*name<<"\n";
                FIInstSelectorManager *fiinstselector = new FIInstSelectorManager;
                fiinstselector->addSelector(im->getCustomInstSelector(*name));
                // errs()<<"# inst selector done on: "<<*name<<"\n";
                FIRegSelector* firegselector = rm->getCustomRegSelector(*name);
                // errs()<<"# reg selector done on: "<<*name<<"\n";
                // select fault injection instructions
                std::set<Instruction*> fiinstset;
                fiinstselector->getFIInsts(M, &fiinstset);
                // errs()<<"# size of inst set: "<<fiinstset.size()<<"\n";
                std::map<Instruction*, std::list< int >* > fi_inst_regs_map;
                // select fault injection registers
                firegselector->getFIInstRegMap(&fiinstset, &fi_inst_regs_map);
                delete fiinstselector;
                // errs()<<"# collection done on: "<<*name<<"\n";
                bool not_empty = false;
                for(std::map<Instruction*, std::list<int>* >::iterator MI = fi_inst_regs_map.begin();
                    MI != fi_inst_regs_map.end(); MI++){
                    if(MI->second->empty()) continue;
                    else    not_empty = true;
                }
                if(not_empty == true){
                    recordInstSelector(*name);
                }
                // errs()<<"# check done on: "<<*name<<"\n";
                for(std::map<Instruction*, std::list<int>* >::iterator MI = fi_inst_regs_map.begin();
                    MI != fi_inst_regs_map.end(); MI++){
                    delete MI->second;
                }
            }
            selector_record_file.close();
        }

        void recordInstSelector(std::string selector_name){
            if(selector_record_file.is_open() == false){
                std::cerr<<"ERROR: can not open file to record applicable selectors: ";
                std::cerr<<outputpath<<"\n";
                selector_record_file.close();
                return;
            }
            selector_record_file<<selector_name<<"\n";
            return;
        }
    };
    char SoftwareFailureAutoScanPass::ID = 0;
    static RegisterPass<SoftwareFailureAutoScanPass> 
        X("SoftwareFailureAutoScanPass", "Automatic scanner of software failure modes", 
            false, false);
}