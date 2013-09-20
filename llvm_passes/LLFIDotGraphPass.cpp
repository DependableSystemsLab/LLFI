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

#include "Utils.h"

#define DATADEPCOLOUR "blue"

using namespace llvm;

namespace llfi {

struct instNode {
  std::string name, label;
  Instruction *raw;
  std::string dotNode();
  instNode(Instruction *target);
};

instNode::instNode(Instruction *target) {
  raw = target;

  long llfiID = llfi::getLLFIIndexofInst(target);
  name = "llfiID_" + longToString(llfiID);

  label = std::string(" [shape=record,label=\"") + longToString(llfiID);
  label += std::string("\\n") + target->getOpcodeName() + "\\n";
  if (target->getDebugLoc().getLine()) {
    label += "(Line #: " + intToString(target->getDebugLoc().getLine()) + ")";
  }
  label += "\"]";
}

std::string instNode::dotNode() {
  return name + label;
}

struct bBlockGraph {
  BasicBlock* raw;
  std::string name;
  std::string funcName;
  std::vector<instNode> instNodes;
  Instruction* entryInst;
  Instruction* exitInst;
  bBlockGraph(BasicBlock *target);
  bool addInstruction(Instruction* inst);
  bool writeToStream(std::ofstream &target);
};

bBlockGraph::bBlockGraph(BasicBlock *BB) {
  raw = BB;
  name = BB->getName().str();
  funcName = BB->getParent()->getNameStr();
  BasicBlock::iterator lastInst;
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
  target << "subgraph cluster_" << funcName << "_" << name << " {\n";
  target << "label = \"" << funcName << "_" << name << "\";\n";
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
  std::ofstream outfs;

  llfiDotGraph() : FunctionPass(ID) {}

  virtual bool doInitialization(Module &M) {
    outfs.open("llfi.stat.graph.dot", std::ios::trunc);
    outfs << "digraph \"LLFI Program Graph\" {\n";
    return false;
  }

  virtual bool doFinalization(Module &M) {
    outfs << "{ rank = sink;"
      "Legend [shape=none, margin=0, label=<"
       "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">"
       " <TR>"
       "  <TD COLSPAN=\"2\"><B>Legend</B></TD>"
       " </TR>"
       " <TR>"
       "  <TD>Normal Control Flow</TD>"
       "  <TD><FONT COLOR=\"black\"> solid arrow </FONT></TD>"
       " </TR>"
       " <TR>"
       "  <TD>Data Dependancy</TD>"
       "  <TD><FONT COLOR=\"blue\"> solid arrow </FONT></TD>"
       " </TR>"
       " <TR>"
       "  <TD>Control Flow Error</TD>"
       "  <TD><FONT COLOR=\"red\">dashed arrow </FONT></TD>"
       " </TR>"
       " <TR>"
       "  <TD>Fault Affected Instruction</TD>"
       "  <TD BGCOLOR=\"YELLOW\"></TD>"
       " </TR>"
       " <TR>"
       "  <TD>Fault Injected Instruction</TD>"
       "  <TD><FONT COLOR=\"red\"> red border </FONT></TD>"
       " </TR>"
       "</TABLE>"
     ">];"
     "}";
    outfs << "}\n";
    outfs.close();
    return false;
  }

  virtual bool runOnFunction(Function &F) {
    //Create handles to the functions parent module and context
    LLVMContext &context = F.getContext();

    std::vector<bBlockGraph> blocks;

    Function::iterator lastBlock;
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
          // TODO: optimize the algorithm below later
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
                  outfs << " [color=\"" << DATADEPCOLOUR << "\"];\n";
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
        BranchInst* exitInst = (BranchInst*)block.exitInst;
        for (unsigned int s = 0; s < exitInst->getNumSuccessors(); s++) {
          BasicBlock* succ = exitInst->getSuccessor(s);
          for (unsigned int d = 0; d < blocks.size(); d++) {
            if (blocks.at(d).raw == succ) {
              std::string from = block.instNodes.back().name;
              std::string to = blocks.at(d).instNodes.front().name;
              outfs << from << " -> "  << to << ";\n";
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
static RegisterPass<llfiDotGraph> X("dotgraphpass", 
  "Outputs a dot graph of instruction execution at runtime", false, false);

}
