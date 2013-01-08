//===- profiling.cpp - Dynamic Instruction Profiling Pass -==//
//
//                     LLFI Distribution
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This pass counts the total number of dynamic instructions under different options:
// a - all instruction types
// b - only compare instruction that is used by a conditional branch
//
// This pass instruments all instructions (satisfying the option specified) with a call to a C tracing function. 
//
// The trace function is a C function which increments the count when the function is executed
// See profiling_lib.c doProfiling() function for more details. This function definition is linked to the instrumented bitcode file (after this pass). 
//
// Finally, at the end of profiling, a call is inserted to endProfiling() function which writes the total dynamic count to a file
//
//
//===----------------------------------------------------------------------===//



#include "profiling.h"

bool ProfilingPass::runOnFunction(Function &F)
{
	LLVMContext& context = F.getContext();
    Module *m = F.getParent();
	string funcname = F.getNameStr();
	string injectfunc("injectFault");
	if((profileoption == 'p' || profileoption == 'c' || profileoption == 'i') && (funcname.find(injectfunc) != string::npos))
		return false;
	for (inst_iterator In = inst_begin(F), E = inst_end(F); In != E; ++In)
    {     
		Instruction *I = dyn_cast<Instruction>(&*In);
		if(profileoption == 'b')
		{
			if(CmpInst *ci = dyn_cast<CmpInst>(I))
				if(is_used_by_branch(ci)){
					vector<const Type*> argTypes(1);
					argTypes[0] = Type::getInt32Ty(context);	// enum for the options
					FunctionType* countFuncType = FunctionType::get( Type::getVoidTy(context), argTypes, 0 );
					Constant* countFunc = m->getOrInsertFunction("doProfiling", countFuncType);			// get the injection function
					vector<Value*> countArgs(1);
					const IntegerType* itype = IntegerType::get(context,32);
					Value* branchVal = ConstantInt::get(itype, BRANCH );

					countArgs[0] = branchVal; //enum for branch
					CallInst* callInst = CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", I); 
				}
		}
		else if(profileoption == 'd')
		{
			//see if the current instruction is a cmp instruction that leads to a conditional branch
			//add the instrumentation to the defs of this cmp instruction
			//--> Static time deduction since branch not known if executed or not
			CmpInst *ci = dyn_cast<CmpInst>(I);
			//errs() <<"reached here:\n";
			if(!ci)
				continue;
	
			//traverse def-use chain
			//int is_used_by_branch = 0;    
	
			if(!is_used_by_branch(I))
				continue;
			//the defines of this instruction I --> would be injectFaultCalls.   
			for (User::op_iterator i = I->op_begin(), e = I->op_end(); i != e; ++i) 
			{    
				Instruction *v = dyn_cast<Instruction>(*i);
				if(!v)
					continue;
				//errs() <<"reached here:"<< *v << "\n"; 
				//do profiling for the def
				vector<const Type*> argTypes(1);
				argTypes[0] = Type::getInt32Ty(context);	// enum for the options
				FunctionType* countFuncType = FunctionType::get( Type::getVoidTy(context), argTypes, 0 );
				Constant* countFunc = m->getOrInsertFunction("doProfiling", countFuncType);			// get the injection function
				vector<Value*> countArgs(1);
				const IntegerType* itype = IntegerType::get(context,32);
				Value* defVal = ConstantInt::get(itype, DEF );
				countArgs[0] = defVal; //enum for branch
				Instruction *beforeInst;
				if(isa<PHINode>(v))
				{	BasicBlock *bb = v->getParent();
					beforeInst = bb->getFirstNonPHI(); 
				}
				else
					beforeInst = v;
				CallInst* callInst = CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst); 	// insert the profiling call before the def:v

			}
		}
		else if(profileoption == 'a' )
		{
			Instruction *beforeInst;
			//consider all instructions profiling
			vector<const Type*> argTypes(1);
			argTypes[0] = Type::getInt32Ty(context);	// enum for the options
			FunctionType* countFuncType = FunctionType::get( Type::getVoidTy(context), argTypes, 0 );
			Constant* countFunc = m->getOrInsertFunction("doProfiling", countFuncType);			// get the injection function
			vector<Value*> countArgs(1);
			const IntegerType* itype = IntegerType::get(context,32);
			Value* allVal = ConstantInt::get(itype, ALL );
			if(isa<PHINode>(I))
			{	BasicBlock *bb = I->getParent();
				beforeInst = bb->getFirstNonPHI(); 
			}
			else
				beforeInst = I;
			countArgs[0] = allVal; //enum for All inst
			CallInst* callInst = CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst); 	// Insert the inject call before the instruction
		}
		else if(profileoption == 's')
		{
			const Type* returnType = I->getType();
			if (returnType->isVoidTy()) 
				continue;
			Instruction *beforeInst;
			//consider all instructions profiling
			vector<const Type*> argTypes(1);
			argTypes[0] = Type::getInt32Ty(context);	// enum for the options
			FunctionType* countFuncType = FunctionType::get( Type::getVoidTy(context), argTypes, 0 );
			Constant* countFunc = m->getOrInsertFunction("doProfiling", countFuncType);			// get the injection function
			vector<Value*> countArgs(1);
			const IntegerType* itype = IntegerType::get(context,32);
			Value* allVal = ConstantInt::get(itype, BACKWARD_SLICE );
			if(isa<PHINode>(I))
			{	BasicBlock *bb = I->getParent();
				beforeInst = bb->getFirstNonPHI(); 
			}
			else
				beforeInst = I;
			countArgs[0] = allVal; //enum for All inst	
			CallInst* callInst = CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst); 	// Insert the inject call before the instruction
		}

    }
    return true;
}
Instruction *ProfilingPass::getFI(Instruction *I){
	for (Value::use_iterator i = I->use_begin(), e = I->use_end(); i != e; ++i){
		Instruction *use = dyn_cast<Instruction>(*i);
		if(use && is_injectFaultFuncCall(use))
			return use;
	}
	return NULL;
}
bool ProfilingPass::doInitialization(Module &M)
{
	LLVMContext& context = M.getContext();
	Function* mainFunc = M.getFunction("main");
	const string moduleName = M.getModuleIdentifier();
	if (mainFunc!=NULL) {
		BasicBlock* entryBlock = &mainFunc->front();
		Constant* Init = ConstantArray::get(context,moduleName,true);	// Convert it to an LLVM Type
		GlobalVariable* nameStr = new GlobalVariable(Init->getType(), true, GlobalValue::InternalLinkage, Init, "NameStr" );	
		M.getGlobalList().push_back( nameStr );						// Insert it into the list of globals for module
		std::vector<Constant*>IndicesC(2);
		IndicesC[0] = Constant::getNullValue(Type::getInt32Ty(context));
		IndicesC[1] = ConstantInt::get(Type::getInt32Ty(context),0);
		Constant *getElemExpr =  ConstantExpr::getGetElementPtr(nameStr, &IndicesC[0], IndicesC.size());
		vector<Value*> initInjectArgs;
		initInjectArgs.push_back( getElemExpr ); 
		FunctionType* initInjectionFuncType = FunctionType::get(Type::getVoidTy(context), 
		vector<const Type*>(1,  PointerType::get(Type::getInt8Ty(context),0)),0); 
		
		BasicBlock *exitBlock = &mainFunc->back();
		Instruction *I;
		for (inst_iterator fi = inst_begin(mainFunc), fe = inst_end(mainFunc); fi!=fe; ++fi){
			I = &*fi;
			if(isa<ReturnInst>(I))
				break;
		}
		BasicBlock *retblock = I->getParent(); //*retpred = retblock->getSinglePredecessor();
		
		Instruction *term = retblock->getTerminator();
		Constant *endFunc = M.getOrInsertFunction("endProfiling", initInjectionFuncType);
		vector<Value*> countArgs(1);
		const IntegerType* itype = IntegerType::get(context,32);
		Value* branchVal = ConstantInt::get(itype, BRANCH );
		CallInst *ci_end = CallInst::Create(endFunc, initInjectArgs.begin(), initInjectArgs.end(), "", term);
	}
     return FunctionPass::doInitialization(M);
}
bool ProfilingPass::doFinalization(Module &M)
{
	return FunctionPass::doFinalization(M);;
}
bool ProfilingPass::is_used_by_branch(Instruction *I)
{
	for (Value::use_iterator i = I->use_begin(), e = I->use_end(); i != e; ++i)
	{
		Instruction *use = dyn_cast<Instruction>(*i);
		BranchInst *bi = dyn_cast<BranchInst>(use);
		if(!bi)
			continue;
		if(bi->isConditional())
		{	return true;}
	}
	return false;
}

bool ProfilingPass::is_injectFaultFuncCall(Instruction *I)
{
	string injectfunc("injectFault");
	CallInst *ci = dyn_cast<CallInst>(I);
	if(!ci)
		return false;
	Function *F = ci->getCalledFunction();
	string funcname;
    if(F)
    funcname = F->getNameStr();
    else
        return false;
    if(funcname.find(injectfunc) != string::npos)
		return true;
	return false;
}

static RegisterPass<ProfilingPass> X("ProfilingPass", "Profiling Pass",false,false);
