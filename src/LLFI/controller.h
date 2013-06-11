#ifndef CONFIG_H
#define CONFIG_H
#include "llvm/Instructions.h"

#include <set>
#include <map>
#include <list>
#include <string>

using namespace llvm;

namespace llfi {
class llvm::Module;
class FIInstSelector;
class FIRegSelector;


enum FIInstSelSrc {
  insttype, sourcecode, custominst
};

enum FIRegSelSrc {
  index, customreg
};

enum FIRegLoc {
  dstreg, allsrcreg, srcreg1, srcreg2, srcreg3, srcreg4
};

class Controller {
  typedef std::map<std::string, unsigned> NameOpcodeMap;
 public:
  static Controller *getInstance(Module &M);
  ~Controller(); 

 public:
  void getFIInstRegsMap(
      std::map<Instruction*, std::list<Value*>* > **fiinstreg) {
    *fiinstreg = &fi_inst_regs_map;
  }
  void dump() const;

 private:
  Controller() {}
  Controller(Module &M) {
    init(M);
  }
  void init(Module &M);
  void processCmdArgs();
  void processInstSelArgs();
  void processRegSelArgs();

  void getOpcodeListofFIInsts(std::set<unsigned> *fi_opcode_set);

 // output of the controller
 private:
  // a map of target instructions and a list of inject loc
  // Assumption: changes on instructions do not have temporal relations
  // That's why we use unordered map instead of list
  // TODO: replace tree-based map to hashtable-based map
  std::map<Instruction*, std::list< Value* >* > fi_inst_regs_map;  

 private:
  FIInstSelector *fiinstselector;
  FIRegSelector *firegselector;

 private:
  static Controller *ctrl;
};

}
#endif
