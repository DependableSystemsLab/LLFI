#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Instruction.h"
#include <cstdio>
#include "Utils.h"

using namespace llvm;
namespace llfi {
class GenLLFIIndexPass: public ModulePass {
 public:
  GenLLFIIndexPass() : ModulePass(ID) {}
	virtual bool runOnModule(Module &M);
	static char ID;
};

char GenLLFIIndexPass::ID = 0;
static RegisterPass<GenLLFIIndexPass> X(
    "genllfiindexpass", "Generate a unique LLFI index for each instruction",
    false, false);

bool GenLLFIIndexPass::runOnModule(Module &M) {
  Instruction *currinst;
  for (Module::iterator m_it = M.begin(); m_it != M.end(); ++m_it) {
    if (!m_it->isDeclaration()) {
      //m_it is a function  
      for (inst_iterator f_it = inst_begin(m_it); f_it != inst_end(m_it);
           ++f_it) {
        currinst = &(*f_it);
        setLLFIIndexofInst(currinst);
      }
    }
  }
  
  if (currinst) {
    long totalindex = getLLFIIndexofInst(currinst);
    FILE *outputFile = fopen("llfi.stat.totalindex.txt", "w");
    if (outputFile)
      fprintf(outputFile, "totalindex=%ld\n", totalindex);

    fclose(outputFile);
  }

  return true;
}

}

