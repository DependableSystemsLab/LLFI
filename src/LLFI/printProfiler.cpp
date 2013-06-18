#include <vector>

#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/GlobalValue.h"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"

using namespace llvm;

namespace {
	struct printProfiler : public FunctionPass {
		static char ID;
		Function::iterator lastBlock;
		BasicBlock::iterator lastInst;

		printProfiler() : FunctionPass(ID) {}

		virtual bool doInitialization(Module &M) {
			return true;
		}

		void profileAndPrintInstruction(Instruction *inst) {

		}

		long fetchLLFIInstructionID(Instruction *targetInst) {
			//TODO: Merge with Jiesheng's instruction assignment
			return 1337; //DUMMY VALUE
		}

		virtual bool runOnFunction(Function &F) {

			//Create handles to the functions parent module and context
			LLVMContext& context = F.getContext();
			Module *M = F.getParent();

			//Create the decleration of the printInstProfile Function with proper arg/return types
			std::vector<const Type*> parameterVector(7 , Type::getInt32Ty(context));//ID, Opcode, Num Ops, Arg0-3 = 6 arguments
			FunctionType* ppFuncType = FunctionType::get(Type::getVoidTy(context), parameterVector, 0 );
			Constant *ppFunc = M->getOrInsertFunction("printInstProfile", ppFuncType); 
			

			//iterate through each basicblock of the function
			for (Function::iterator blockIterator = F.begin(), lastBlock = F.end();
				blockIterator != lastBlock; ++blockIterator) {

				//Iterate through each instruction of the basicblock
				for (BasicBlock::iterator instIterator = blockIterator->begin(), 
					 lastInst = blockIterator->end(); 
					 instIterator != lastInst;
					 ++instIterator) {

					//Print some Debuf Info as the pass is being run
					Instruction *inst = instIterator;
					errs() << "printProfiler: Found Instruction\n"
						   << "   Opcode: " << inst->getOpcodeName() << "\n"
						   << "   Parent Function Name: " << inst->getParent()->getParent()->getNameStr() << "\n";

					//Insert the printProfiling function, passing it the proper arguments
					std::vector<Value*> ppArgs;
					//Fetch the LLFI Instruction ID:
					ConstantInt* IDConstInt = ConstantInt::get(IntegerType::get(context,32), fetchLLFIInstructionID(inst));
					//Fetch the OPcode:
					ConstantInt* OPConstInt = ConstantInt::get(IntegerType::get(context,32), inst->getOpcode());
					//Fetch the number of operands passed to the instruction:
					unsigned numInstOperands = inst->getNumOperands();
					ConstantInt* NumOpsConstInt = ConstantInt::get(IntegerType::get(context,32), numInstOperands);
					//Load All Arguments
					ppArgs.push_back(IDConstInt);
					ppArgs.push_back(OPConstInt);
					ppArgs.push_back(NumOpsConstInt);

					//Sam: I'm not sure if this is a good way to handle fetching the arguments to the instruction.
					//	   Ideally, this would capture up to 4 integer arguments to every instruction but im not
					//	   100% sure about reliability. Also, if there are less than 4 arguments it will just pass
					//	   out a '0'... which could confuse analysis if '0' is actually a legitimate argument.
					//UPDATE: This whole methodology is broken... we need to be fetching argument values at runtime,
					//		  NOT at 'Pass' time... How do we do this!?
					//#TODO: Come back to this later. || Try passing a pointer value to the pPLib function... then let
					//									 the library function evaluate what the pointer points to.
					//Fetch up to 4 arguments to the instruction as integers
					unsigned i;
					for (i = 0; i < numInstOperands; ++i) {
						int val;
						if (ConstantInt* CI = dyn_cast<ConstantInt>(inst->getOperand(i))) {
							val = CI->getSExtValue();
						}
						else {
							val = 0;
						}
						ppArgs.push_back(ConstantInt::get(IntegerType::get(context,32), val));
					}
					for (; i < 4; ++i) {
						ppArgs.push_back(ConstantInt::get(IntegerType::get(context,32), 0));
					}

					//Create the Function.
					//CallInst* callInstruction = //Not Needed #CULL
					CallInst::Create(ppFunc, ppArgs.begin(),ppArgs.end(), "", inst);

				}

			}

			return true; //Tell LLVM that the Function was modified
		}
	};
}

//Register the pass with the llvm
char printProfiler::ID = 0;
static RegisterPass<printProfiler> X("printProfiler", "Profiles the code by printing instruction Info", false, false);
