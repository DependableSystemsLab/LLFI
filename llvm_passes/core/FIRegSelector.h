#ifndef FI_REG_SELECTOR_H
#define FI_REG_SELECTOR_H
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"
#include "Controller.h"

#include <set>
#include <map>
#include <list>
#include <string>

using namespace llvm;
namespace llfi {
class FIRegSelector {
 public:
  void getFIInstRegMap(const std::set< Instruction* > *instset, 
                std::map<Instruction*, std::list< int >* > *instregmap);
  virtual std::string getRegSelectorClass(){
  	return std::string("Unknown");
  }

 private:
  virtual bool isRegofInstFITarget(Value *reg, Instruction *inst) = 0;
  virtual bool isRegofInstFITarget(Value* reg, Instruction* inst, int pos);
  // determine whether LLFI is able to inject into the specified reg or not
  bool isRegofInstInjectable(Value *reg, Instruction *inst);
};

class SoftwareFIRegSelector: public FIRegSelector {
	virtual std::string getRegSelectorClass(){
		return std::string("SoftwareFault");
	}
};

class HardwareFIRegSelector: public FIRegSelector {
	virtual std::string getRegSelectorClass(){
		return std::string("HardwareFault");
	}
};

}

#endif
