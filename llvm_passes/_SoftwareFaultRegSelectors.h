#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "FIInstSelector.h"
#include "FIRegSelector.h"
#include "FICustomSelectorManager.h"

#include "llvm/IR/IntrinsicInst.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
namespace llfi {
	class FuncArgRegSelector: public FIRegSelector {
	public:
		FuncArgRegSelector(int target_arg) : pos_argument(target_arg), specified_arg(true) {};
		FuncArgRegSelector():pos_argument(0), specified_arg(false) {};
	private:
		int pos_argument;
		bool specified_arg;
		virtual bool isRegofInstFITarget(Value *reg, Instruction *inst);
	};
	
	class FuncDestRegSelector: public FIRegSelector {
	private:
		virtual bool isRegofInstFITarget(Value *reg, Instruction *inst);
	};

	class RetValRegSelector: public FIRegSelector {
	private:
		virtual bool isRegofInstFITarget(Value *reg, Instruction *inst);
	};

}

 
