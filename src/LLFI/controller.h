#ifndef CONFIG_H
#define CONFIG_H

#include <set>
#include <map>
#include <list>
#include <string>
#include "llvm/Instructions.h"

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
  destreg, allsrcreg, srcreg1, srcreg2, srcreg3, srcreg4
};

// TODO: change it to singleton model
class Controller {
  typedef std::map<std::string, unsigned> NameOpcodeMap;
 public:
  void init(Module *M);
 public:
  ~Controller(); 

 public:
  void getFIInstRegsMap(std::map<Instruction*, std::list<Value*>* > **fiinstreg) {
    *fiinstreg = &fi_inst_regs_map;
  }
  void dump() const;

 private:
  void processCmdArgs();
  void processInstSelArgs();
  void processRegSelArgs();

  void getOpcodeListofFIInsts(std::set<unsigned> *fi_opcode_list);
  void genFullNameOpcodeMap(NameOpcodeMap &opcodenamemap);

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
};

}
#endif
