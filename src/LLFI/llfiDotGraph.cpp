#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Target/TargetData.h"

#include "utils.h"

using namespace llvm;

namespace llfi {

struct bBlock {
	BasicBlock* raw;
	std::string name;
	std::string funcName;
	std::vector<std::string> instStrings;
	Instruction* entryInst;
	Instruction* exitInst;
	int nonLLFIinstCount;
	bBlock(BasicBlock *target);
	bool addInstruction(Instruction* inst);
	bool writeToStream(std::ofstream &target);
};
bBlock::bBlock(BasicBlock *BB) {
	raw = BB;
	nonLLFIinstCount = 0;
	name = BB->getName().str();
	funcName = BB->getParent()->getNameStr();
	for (BasicBlock::iterator instIterator = BB->begin(), 
		 lastInst = BB->end(); 
		 instIterator != lastInst;
		 ++instIterator) {

		Instruction *inst = instIterator;

		addInstruction(inst);	

	}
	entryInst = &(BB->front());
	exitInst = &(BB->back());
}
bool bBlock::addInstruction(Instruction* inst) {
	std::stringstream Node;
	Node << funcName << "_" << name << "_" << inst->getOpcodeName() << "_";			
	if (llfi::isLLFIIndexedInst(inst)) {
		Node << "llfiID_" << llfi::getLLFIIndexofInst(inst);
	} else {
		Node << "bBlockID_" << nonLLFIinstCount;
		nonLLFIinstCount++;
	}
	instStrings.push_back(Node.str());

	return true;	
}

bool bBlock::writeToStream(std::ofstream &target) {
	for (unsigned int i = 0; i < instStrings.size(); i++) {
		target << instStrings.at(i) << " [shape=record];\n";
	}
	for (unsigned int i = 1; i < instStrings.size(); i++) {
		target << instStrings.at(i-1) << " -> " << instStrings.at(i) << ";\n";
	}
	return true;
}

struct llfiDotGraph : public FunctionPass {

static char ID;
Function::iterator lastBlock;
BasicBlock::iterator lastInst;
std::ofstream outfs;
int nonllfiInstIndex;

llfiDotGraph() : FunctionPass(ID) {}

virtual bool doInitialization(Module &M) {
	outfs.open("LLFIDOTGRAPHOUTPUT.dot", std::ios::trunc);
	outfs << "digraph \"TestGraph\" {\n";
	nonllfiInstIndex = 0;
	errs() << nonllfiInstIndex << " ";
	return false;
}

virtual bool doFinalization(Module &M) {
	outfs << "}\n";
	outfs.close();
	return false;
}

virtual bool runOnFunction(Function &F) {
	//Create handles to the functions parent module and context
	LLVMContext& context = F.getContext();
	Module *M = F.getParent();

	std::vector<bBlock> blocks;			

	//iterate through each basicblock of the function
	for (Function::iterator blockIterator = F.begin(), lastBlock = F.end();
		blockIterator != lastBlock; ++blockIterator) {

		BasicBlock* block = blockIterator;

		bBlock b(block);
		blocks.push_back(b);

	}

	for (unsigned int i = 0; i < blocks.size(); i++) {
		bBlock block = blocks.at(i);
		block.writeToStream(outfs);
		if (block.exitInst->getOpcode() == Instruction::Br) {
			outfs << "#Found BR inst\n";
			BranchInst* exitInst = (BranchInst*)block.exitInst;
			for (unsigned int s = 0; s < exitInst->getNumSuccessors(); s++) {
				BasicBlock* succ = exitInst->getSuccessor(s);
				outfs << "#" << exitInst->getNumSuccessors() << "\n";
				for (unsigned int d = 0; d < blocks.size(); d++) {
					if (blocks.at(d).raw == succ) {
						outfs << "#Found matching successor\n";
						std::string from = block.instStrings.back();
						std::string to = blocks.at(d).instStrings.front();
						outfs << from << " -> "	<< to << ";\n";
					}
				}
			}
		}
	}

	return false;
}

};

//Register the pass with the llvm
char llfiDotGraph::ID = 0;
static RegisterPass<llfiDotGraph> X("llfiDotGraph", 
	"Outputs a dot graph of instruction execution at runtime", false, false);

}