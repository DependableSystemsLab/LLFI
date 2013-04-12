#ifndef FAULTINJECT_H

#define FAULTINJECT_H

#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/InstVisitor.h"
#include "llvm/Support/Debug.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/Dominators.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AliasSetTracker.h"
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Support/CommandLine.h"

// STL includes
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <string>
#include <utility>


//----------Parameter types-------------
#define INTEGER  1
#define ARRAY 2
#define STRUCT 3
#define POINTER 4
#define FLOAT 5
#define DOUBLE 6
//--------------------------------------

//----------Fault information-----------
#define BIT_BYTE_WHOLE_FLAG_POS 0
#define INCLUSIVE_FLAG_POS 1
#define LOWERBOUND_POS 2
#define UPPERBOUND_POS 3
#define BIT_FAULT 0
#define BYTE_FAULT 1
#define WHOLE_FAULT 2
//-------------------------------------- //

using namespace llvm;
using namespace std;
// if no fioption, faults injected at all instruction
//options are :
//all (all injection)
//nobranch (injection everything except branch)
//nobranchnobcv (injection everything except branch and bcv)
static cl::opt<string> fioption("fioption", cl::desc("The option for Fi: branch (b) or defs(d)! or all(a) or backward slice (s)"), cl::value_desc("fioption"));

namespace
{
class FaultInjectionRandom:public FunctionPass {
  public:
    FaultInjectionRandom() : FunctionPass(ID), ptrinstnum(0), cmpinstnum(0), totalinstnum(0) {
		all = "all";
		nobranch = "nobranch";
		nobranchnobcv = "nobranchnobcv";
		onlybranch = "Branch";
	}
	virtual bool doInitialization(Module &M);
	virtual bool runOnFunction(Function &F);	
	virtual bool doFinalization(Module& M);
	static char ID; // Pass identification, replacement for typeid
	virtual void getAnalysisUsage(AnalysisUsage &AU) const {
	    AU.addRequired<TargetData>();
	    AU.addRequired<DominatorTree>();
	    AU.addRequired<AliasAnalysis>();		// Make sure that some Alias Analysis is computed before this pass	

       }
  private:
	map<const Type*, string> FiFuncName;				// Map of fault-injection function names and types
	int faultIndex; 						// index of instruction for fault-injection purposes
	map<Instruction*, Instruction*> FaultIndexMap;			// Map of instructions to their fault-indices
		set<Instruction*> fixupSet;			// Working set of all instructions that need to be converted to loads and stores
	enum function_type {FAULTINJECT, TRACE}; //can add more types for tracing
	void insertInjectionFunc(set<Instruction*>&, Module*);
	void createInjectionFunc(Module*, const Type*, string&, Constant*, Constant*);
	void createInjectionFunctions(Module* m);
	void printFaultIndices(Module *M);
	Instruction* findInstrumentationPoint(Instruction* Insn);
	bool is_branch_or_datavar(Instruction *I, Instruction *fi);
	Instruction* insertPrintStatement(string& checkStr, Value* printVal, Instruction* I);
	uint64_t getStaticId(Instruction *I); //get the static id of the fault injection hook for I
	bool is_injectFaultFuncCall(Instruction *I);
	void getStaticInstances();
	bool is_used_by_branch(Instruction *I);
	//void remove_other_FIs(Module &M);	
	std::string Filenamebranch, Filenamedatavar, ErrorInfo;
	fstream branchstaticfile, datavarstaticfile;
	
	string all;
	string nobranch;
	string nobranchnobcv, onlybranch;

	//-----------------------FOR filter USE-------------------------
	map<string, vector<pair<unsigned int, int> > > map_func_argu; //Qining
	map<string, vector<int> > map_func_fault_range; //Qining
	map<string, set<unsigned int> > map_func_fault_type; //Qining
	map<string, int > map_func_bit_byte_whole; //Qining
	int bit_byte_whole_flag;
	bool filter(Instruction *I); //filter function
	int searchArgument(string func_name, int pos);
	//--------------------------------------------------------------

  // Stat purpose //Jiesheng
  unsigned long ptrinstnum;
  unsigned long cmpinstnum;
  unsigned long totalinstnum;

};
}
char FaultInjectionRandom::ID=0;

#endif
