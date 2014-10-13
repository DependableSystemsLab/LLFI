#include "llvm/IR/Instructions.h"
#include "llvm/Support/CommandLine.h"

#include "FIInstSelector.h"
#include "FICustomSelectorManager.h"
#include "Utils.h"

using namespace llvm;

namespace llfi {

static cl::list< std::string > injecttoindex("injecttoindex", 
    cl::desc("Inject into the specified LLFI index"), 
    cl::ZeroOrMore);

/**
 * LLFI Index instruction selector selects instruction of certain indices
 */
class LLFIIndexFIInstSelector: public FIInstSelector {
 private:
  virtual bool isInstFITarget(Instruction *inst) {
    long llfiindex = getLLFIIndexofInst(inst);
    for (unsigned i = 0; i != injecttoindex.size(); ++i)
      if (atol(injecttoindex[i].c_str()) == llfiindex)
        return true;
    return false;
  }
 public:
  virtual void getCompileTimeInfo(std::map<std::string, std::string>& info){
    info["failure_class"] = "HardwareFault";
    info["failure_mode"] = "SpecifiedLLFIIndex";
    info["targets"] = "<include list in yaml>";
    info["injector"] = "<fi_type>";
  }
};

static RegisterFIInstSelector X("llfiindex", new LLFIIndexFIInstSelector());
}
