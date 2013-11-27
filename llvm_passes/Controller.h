#ifndef CONFIG_H
#define CONFIG_H
#include "llvm/Instructions.h"
#include "llvm/Module.h"

#include <set>
#include <map>
#include <list>
#include <string>

using namespace llvm;

namespace llfi {
class FIInstSelectorManager;
class FIRegSelector;


enum FIInstSelMethod {
  insttype, funcname, sourcecode, custominstselector
};

enum FIRegSelMethod {
  regloc, customregselector
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
  void getFuncList(std::set<std::string> *fi_func_set);
  void getModuleFuncs(Module &M);

 // output of the controller
 private:
  // a map of target instructions and a list of inject loc
  // Assumption: changes on instructions do not have temporal relations
  // That's why we can use unordered map instead of list
  // TODO: replace tree-based map to hashtable-based map for performance
  std::map<Instruction*, std::list< Value* >* > fi_inst_regs_map;  

 private:
  FIInstSelectorManager *fiinstselector;
  FIRegSelector *firegselector;

  // set of functions present in module
  std::set<std::string> func_set;

 private:
  static Controller *ctrl;
};

}
#endif
