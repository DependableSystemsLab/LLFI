#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include "FIRegSelector.h"

using namespace llvm;

namespace llfi {

extern cl::opt< std::string > llfilogfile;

void FIRegSelector::getFIInstRegMap(
    const std::set< Instruction* > *instset, 
    std::map<Instruction*, std::list< int >* > *instregmap) {
  std::string err;
  raw_fd_ostream logFile(llfilogfile.c_str(), err, sys::fs::F_Append);

  for (std::set<Instruction*>::const_iterator inst_it = instset->begin();
       inst_it != instset->end(); ++inst_it) {
    Instruction *inst = *inst_it;
    std::list<int> *reglist = new std::list<int>();
    // dstination register
    if (isRegofInstFITarget(inst, inst)) {
      if (isRegofInstInjectable(inst, inst))
        reglist->push_back(DST_REG_POS);
      else if (err == "") {
        logFile << "LLFI cannot inject faults in destination reg of " << *inst
              << "\n";
      }
    }
    // source register
    int pos = 0;
    for (User::op_iterator op_it = inst->op_begin(); op_it != inst->op_end();
         ++op_it, ++pos) {
      Value *src = *op_it;
      if (isRegofInstFITarget(src, inst, pos)) {
        if (isRegofInstInjectable(src, inst)) {
          reglist->push_back(pos);
          //dbgs()<<"srcreg "<<" inst:"<<*inst<<" reg:"<<*inst->getOperand(pos)<<" pos:"<<pos<<"\n";
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
          std::pair<Instruction*, std::list< int >* >(inst, reglist));
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

bool FIRegSelector::isRegofInstFITarget(Value* reg, Instruction* inst, int pos){
  return isRegofInstFITarget(reg, inst);
}

}
