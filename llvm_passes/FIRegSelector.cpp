#include "llvm/Instructions.h"
#include "llvm/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include "FIRegSelector.h"

using namespace llvm;

namespace llfi {

extern cl::opt< std::string > llfilogfile;

void FIRegSelector::getFIInstRegMap(
    const std::set< Instruction* > *instset, 
    std::map<Instruction*, std::list< Value* >* > *instregmap) {
  std::string err;
  raw_fd_ostream logFile(llfilogfile.c_str(), err, raw_fd_ostream::F_Append);

  for (std::set<Instruction*>::const_iterator inst_it = instset->begin();
       inst_it != instset->end(); ++inst_it) {
    Instruction *inst = *inst_it;
    std::list<Value*> *reglist = new std::list<Value*>();
    // dstination register
    if (isRegofInstFITarget(inst, inst)) {
      if (isRegofInstInjectable(inst, inst))
        reglist->push_back(inst);
      else if (err == "") {
        logFile << "LLFI cannot inject faults in destination reg of " << *inst
              << "\n";
      }
    }
    // source register
    for (User::op_iterator op_it = inst->op_begin(); op_it != inst->op_end();
         ++op_it) {
      Value *src = *op_it;
      if (isRegofInstFITarget(src, inst)) {
        if (isRegofInstInjectable(src, inst)) {
          reglist->push_back(src);
        } else if (err == "") {
          logFile << "LLFI cannot inject faults in source reg ";
          if (isa<BasicBlock>(src)) 
            logFile << src->getName();
          else
            logFile << *src;
          logFile << " of instruction " << *inst << "\n";
        }
      }
    }
    
    if (reglist->size() != 0) {
      instregmap->insert(
          std::pair<Instruction*, std::list< Value* >* >(inst, reglist));
    } else if (err == "") {
      logFile << "The selected instruction " << *inst << 
          "does not have any valid registers for fault injection\n";
    }
  }
  logFile.close();
}

bool FIRegSelector::isRegofInstInjectable(Value *reg, Instruction *inst) {
  // TODO: keep updating
  // if we find anything that can be covered, remove them from the checks
  // if we find new cases that we cannot handle, add them to the checks
  if (reg == inst) {
    if (inst->getType()->isVoidTy() || isa<TerminatorInst>(inst)) {
      return false;
    }
  } else {
    if (isa<BasicBlock>(reg) || isa<PHINode>(inst))
      return false;
  }
  return true;
}

}
