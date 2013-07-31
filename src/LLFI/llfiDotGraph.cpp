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

struct instNode {
	std::string name, label, shape;
	Instruction *raw;
	std::string dotNode();
	instNode(Instruction *target);
};

instNode::instNode(Instruction *target) {
	raw = target;

	int llfiID = llfi::getLLFIIndexofInst(target);
	std::stringstream nodeName;
	std::string bbname = target->getParent()->getName().str();
	std::string funcName = target->getParent()->getParent()->getNameStr();
	nodeName << funcName << "_" << bbname << "_" << target->getOpcodeName() << "_";
	nodeName <<	"llfiID_" << llfiID;
	name = nodeName.str();

	std::stringstream labelStream;
	labelStream << " [shape=record,label=\"" << llfiID << "\"]";
	label = labelStream.str();
}

std::string instNode::dotNode() {
	std::stringstream dotnode;
	dotnode << name << label;
	return dotnode.str();
}

struct bBlockGraph {
	BasicBlock* raw;
	std::string name;
	std::string funcName;
	std::vector<instNode> instNodes;
	Instruction* entryInst;
	Instruction* exitInst;
	int nonLLFIinstCount;
	bBlockGraph(BasicBlock *target);
	bool addInstruction(Instruction* inst);
	bool writeToStream(std::ofstream &target);
};

bBlockGraph::bBlockGraph(BasicBlock *BB) {
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
bool bBlockGraph::addInstruction(Instruction* inst) {
	instNodes.push_back(instNode(inst));

	return true;	
}

bool bBlockGraph::writeToStream(std::ofstream &target) {
	target << "subgraph cluster_" << funcName << "_" << name << "{\n";
	for (unsigned int i = 0; i < instNodes.size(); i++) {
		target << instNodes.at(i).dotNode() << ";\n";
	}
	target << "}\n";
	for (unsigned int i = 1; i < instNodes.size(); i++) {
		target << instNodes.at(i-1).name << " -> " << instNodes.at(i).name << ";\n";
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

	std::vector<bBlockGraph> blocks;			

	//iterate through each basicblock of the function
	for (Function::iterator blockIterator = F.begin(), lastBlock = F.end();
		blockIterator != lastBlock; ++blockIterator) {

		BasicBlock* block = blockIterator;

		bBlockGraph b(block);
		blocks.push_back(b);

	}
	for (unsigned int i = 0; i < blocks.size(); i++) {
		bBlockGraph currBlock = blocks.at(i);
		for (unsigned int i = 0; i < currBlock.instNodes.size(); i++) {
			Instruction *inst = currBlock.instNodes.at(i).raw;
			std::string nodeName = currBlock.instNodes.at(i).name;
			instNode node = currBlock.instNodes.at(i);
			if (!inst->use_empty()) {
				for (value_use_iterator<User> useIter = inst->use_begin();
				     useIter != inst->use_end(); useIter++) {
					Value* userValue = *useIter;
					for (unsigned int f = 0; f < blocks.size(); f++) {
						bBlockGraph searchBlock = blocks.at(f);
						for (unsigned int d = 0; d < searchBlock.instNodes.size(); d++) {
							Instruction* targetInst = searchBlock.instNodes.at(d).raw;
							if (userValue == targetInst) {
								instNode targetNode = searchBlock.instNodes.at(d);
								outfs << nodeName << " -> " << targetNode.name;
								outfs << " [color=\"red\"];\n";
							}
						}
					}
				}
			}
		}
	}

	for (unsigned int i = 0; i < blocks.size(); i++) {
		bBlockGraph block = blocks.at(i);
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
						std::string from = block.instNodes.back().name;
						std::string to = blocks.at(d).instNodes.front().name;
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