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
	std::vector<Instruction*> insert_worklist;
	for (inst_iterator In = inst_begin(F), E = inst_end(F); In != E; ++In)
    {     
		Instruction *I = dyn_cast<Instruction>(&*In);
		//errs()<<*I<<"\n";
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
					CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", I); 
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
				CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst); 	// insert the profiling call before the def:v

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
			CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst); 	// Insert the inject call before the instruction
		}
		//in fact, here we only use backwardslice ('s')
		else if(profileoption == 's')
		{
			const Type* returnType = I->getType();
			if (returnType->isVoidTy() || !filter(I))//Here we can insert a new filter ///////////////////////////////////////////////
			{
				//errs()<<"filter not passed\n";
				continue;
			}
			
			//errs()<<"filter passed\n";
			Instruction *beforeInst;
			if(isa<PHINode>(I))
			{	BasicBlock *bb = I->getParent();
				beforeInst = bb->getFirstNonPHI(); 
			}
			else
				beforeInst = I;
			insert_worklist.push_back(beforeInst);
		}

    }

    while(!insert_worklist.empty())
    {
    	Instruction* beforeInst = insert_worklist.back();
    	insert_worklist.pop_back();
    	vector<const Type*> argTypes(1);
			argTypes[0] = Type::getInt32Ty(context);	// enum for the options
			FunctionType* countFuncType = FunctionType::get( Type::getVoidTy(context), argTypes, 0 );
    	Constant* countFunc = m->getOrInsertFunction("doProfiling", countFuncType);
    	vector<Value*> countArgs(1);
    		const IntegerType* itype = IntegerType::get(context,32);
			Value* allVal = ConstantInt::get(itype, BACKWARD_SLICE );
    		countArgs[0] = allVal; //enum for All inst

    	CallInst::Create( countFunc, countArgs.begin(),countArgs.end(), "", beforeInst);

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
		//BasicBlock* entryBlock = &mainFunc->front();
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
		
		//BasicBlock *exitBlock = &mainFunc->back();
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
		//const IntegerType* itype = IntegerType::get(context,32);
		//Value* branchVal = ConstantInt::get(itype, BRANCH );
		CallInst::Create(endFunc, initInjectArgs.begin(), initInjectArgs.end(), "", term);
	}
	else
	{
		Constant* Init = ConstantArray::get(context,moduleName,true);	// Convert it to an LLVM Type
		GlobalVariable* nameStr = new GlobalVariable(Init->getType(), true, GlobalValue::InternalLinkage, Init, "NameStr" );
		M.getGlobalList().push_back( nameStr );
	}

	//***********************************************************************************************************
	//code for loading configure file should be here
	ifstream config ("llfi_configure.txt");
	if (config.is_open())
	{
		// we need to extract information from config file here Qining
		// this loop is used to know if the file is end
		while ( config.good() )
    	{
    		string line;
      		getline (config,line);
      		if(line.empty())	continue;
      		//if the line is empty, just skip.
      		//Any block of configure is started with one specific function
      		unsigned found = line.find("FUNCTION_NAME:");
      		if (found < line.length())
      		{
    			//std::cout << "\nfound FUNCTION_NAME at " << found << '\n';
    			std::string func_name = line.substr (found + string("FUNCTION_NAME:").length(),line.length() - found - string("FUNCTION_NAME:").length());
    			//first, I need to trim it
    			while(func_name[0] == ' ')
    			{
    				func_name.erase(0, 1);
    			}
    			while(func_name[func_name.length() - 1] == ' ')
    			{
    				func_name.erase(func_name.length() - 1, 0);
    			}
    			//so now I've got the name of the function
    			if(func_name.empty())	continue;
				std::cout << "The func_name is " << func_name << "\n";
				map_func_argu[func_name] = set<unsigned int>(); // create entry
				//map_func_fault_type[func_name] = set<unsigned int>(); 
				//second, I need to load argument set and type set
				do
				{
					line.clear();
					getline(config,line); // get the next line
					if(!config.good())	break; // if the new line is the end of file, our job is done.
					if(line.find("ARGUMENT:") < line.length())
					{
						//insert argument id to argument set
						std::string arg_set = line.substr(line.find("ARGUMENT:")+string("ARGUMENT:").length(), line.length() - line.find("ARGUMENT:")-string("ARGUMENT:").length());
						std::string arg;
						while(!arg_set.empty())
						{
							while(arg_set[0] <= '9' && arg_set[0] >= '0')
							{
								arg.append(arg_set.substr(0,1));
								if(!arg_set.empty())	arg_set.erase(0,1);
							}
							if(!arg.empty())
							{
								unsigned int arg_num = atoi(arg.c_str()) - 1;
								map_func_argu[func_name].insert(arg_num);
								std::cout << "\tinclude arg: " << arg_num+1 << "\n";
							}
							arg.clear();
							if(!arg_set.empty())	arg_set.erase(0,1);

						}
					}

				}while(line.find("FUNC_DEF_END") != 0);

    		}

    	}
    	// The file is end, we should have already finished our work, now close the file
    	config.close();
	}
	else errs()<<"Unable to open config file, use default config: all instructions, one bit flip\n";
	//***********************************************************************************************************

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

bool ProfilingPass::filter(Instruction *I)
{
	if(map_func_argu.empty())	
		{
			//bit_byte_whole_flag = BIT_FAULT;
			return true;
		}

	//if this variable is a function pointer, we skip it now
	if(const PointerType* ptr_ty = dyn_cast<PointerType>(I->getType()))
	{
		if(isa<FunctionType>(ptr_ty->getElementType()))
		{
			return false;
		}
	}
	//only check when there is a list of function
	for(Value::use_iterator UI = I->use_begin(), UE = I->use_end(); UI != UE; ++UI)
	{
		Instruction *user = cast<Instruction>(*UI);
		if(CallInst* callinst = dyn_cast<CallInst>(user))
		{
			Function* func_called = callinst->getCalledFunction();
			//check function
			//skip indirect call
			if(func_called==NULL)
			{
				//errs()<<"\nCall function pointer\n";
				return false;
			}
			string funcname = func_called->getName();
			if(!map_func_argu.count(funcname))	continue;
			//check argument
			unsigned int argu_i = 0;
			for(argu_i = 0; argu_i < callinst->getNumOperands(); argu_i++)
			{
				if(callinst->getOperand(argu_i) == I)	break;
			}
			if(argu_i == callinst->getNumOperands())	continue;
			//if the argument set is empty, all arguments are candidates for insertion
			if(!map_func_argu.find(funcname)->second.count(argu_i) && !map_func_argu.find(funcname)->second.empty())	continue;
			return true;
		}
		else
		{
			continue;
		}

	}
	
	return false;
}

static RegisterPass<ProfilingPass> X("ProfilingPass", "Profiling Pass",false,false);
