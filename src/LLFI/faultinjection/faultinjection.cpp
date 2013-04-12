//===- faultinjection.cpp - Fault Injection Pass -==//
//
//                     LLFI Distribution
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This pass instruments each instruction (except instructions with no return value) with calls to fault injection function
//
// The fault injection function is a C function which performs the single bit flip. 
// See fi_random.c injectFunc() function for more details on the fault injection function. This function definition is linked to the instrumented bitcode file (after this pass). 
//
//
//===----------------------------------------------------------------------===//

#include "faultinjection.h"

//Acknowledgement: Used parts of Karthik's code

Instruction* FaultInjectionRandom::findInstrumentationPoint(Instruction *Insn) {
	//DEBUG( cerr << "Finding instrumentation point for basic block " << bb->getName() << "\n"; );
	// skip over the phiNodes and Alloca Instructions at the beginning of the basic block
	// If Insn is a PHI, then other InjectFault instructions should also be skipped. Qining
	Instruction* instrumentInsn;
	BasicBlock *bb = Insn->getParent();
	BasicBlock::iterator ii, ie;
	for (ii = bb->begin(), ie = bb->end(); ii!=ie; ++ii) {
		Instruction* I = &(*ii);
		if(isa<PHINode>(Insn))
		{  if (! dyn_cast<PHINode>(I) && ! dyn_cast<AllocaInst>(I) && !is_injectFaultFuncCall(I) ) break; }
		else if(I==Insn)
		{	++ii; break; }
		  
	}
	
	// Find the first instruction after the instrumented instructions
	instrumentInsn = &(*ii);
	DEBUG( errs()<<"Found instrumentation point : " << *instrumentInsn << " in basic block " << bb->getName() << "\n"; );
	return instrumentInsn;
}

void FaultInjectionRandom::insertInjectionFunc(set<Instruction*>& insnSet, Module* M) {
	// Get or create an injection function of the appropriate type (taking I as argument and returning type I)
	for (set<Instruction*>::iterator si = insnSet.begin(), se = insnSet.end(); si!=se; ++si) {
		Instruction* I = *si;
		const Type* returnType = I->getType();
		if (returnType->isVoidTy() || !filter(I)) //here we can insert a filter
		  continue;
		

    // Jiesheng
    if (returnType->isPointerTy())
      ptrinstnum++;
    if (isa<CmpInst>(I))
      cmpinstnum++;
    totalinstnum++;




		vector<const Type*> argTypes(4); // Qining, add one more argument to determing bit,byte or whole
		LLVMContext& context = M->getContext();
		argTypes[0] = Type::getInt32Ty(context);	// Fault-index number
		argTypes[1] = Type::getInt32Ty(context); // the Enum saying if it is TRACE or FAULTINJECT
		argTypes[2] = returnType;	// Actual value
		argTypes[3] = Type::getInt32Ty(context); // bit, byte or whole flag
		FunctionType* injectFuncType = FunctionType::get( returnType, argTypes, 0 );
		string funcName;
		if ( FiFuncName.find( returnType )!= FiFuncName.end() ) {
			funcName = FiFuncName[ returnType ];
		} else {
			char fiStr[20];
			int fiCount = FiFuncName.size();	
			sprintf(fiStr, "injectFault%d", fiCount);
			funcName = string(fiStr);
			FiFuncName[returnType] = funcName;
		}
		Constant* injectFunc = M->getOrInsertFunction(funcName, injectFuncType);
		++faultIndex;
		int size = argTypes[0]->getPrimitiveSizeInBits();
		const IntegerType* itype = IntegerType::get(context,size);
		Value* indexVal = ConstantInt::get(itype, faultIndex );
		
		vector<Value*> args(4); // Qining, bit, byte or whole flag
		args[0] = indexVal;
		Constant *faultinjectval = ConstantInt::get(Type::getInt32Ty(context),FAULTINJECT); //always fault inject. if tracing required, add separately.
		args[1] = faultinjectval;
		args[2] = I;
		args[3] = ConstantInt::get(Type::getInt32Ty(context), bit_byte_whole_flag); // Qining, bit, byte or whole flag
		char indexStr[20];
		sprintf(indexStr, "%d", faultIndex);
		Instruction* insertInst;
		insertInst = findInstrumentationPoint(I);
		string fiName = "fi" + string(indexStr);
		Instruction* callInst = CallInst::Create( injectFunc, args.begin(),args.end(), fiName, insertInst);
		// Replace the uses of the original instruction with the return value from the function
		I->replaceAllUsesWith( callInst );
		callInst->replaceUsesOfWith(callInst, I);
		FaultIndexMap[I] = callInst;
		//DEBUG( cerr<<"Call instruction : "<< *callInst );
		//errs() << "Call Inst:" << *callInst << "\n";
	}
}

//Pre  takes care of checking if fault should be injected 
void FaultInjectionRandom::createInjectionFunc(Module* m, const Type* fiType, string& fiName, Constant* injectFunc, Constant* preFunc) {
	DEBUG( cerr<<"Creating fault injection function : "<< fiName <<"\n");
	LLVMContext& context = m->getContext();
	
	Function* f = m->getFunction( fiName );
	vector<Value*> args;
	for(Function::arg_iterator ai = f->arg_begin(), ae = f->arg_end(); ai!=ae; ++ai)
		args.push_back(&*ai);
	// Insert call to prefix function
	BasicBlock* entryBlock = BasicBlock::Create(context, "entry", f );		// create an entry block for the func()
	
	vector<Value*> preArgs(4); // Qining, bit_byte_whole_flag, add one more for appName
	preArgs[0] = args[0]; //FI Number
	
	preArgs[1] = args[1]; // the ENUM
	const Type* argType = args[2]->getType();			// Get the type of the value being injected
	int size = 0;
	TargetData& td = getAnalysis<TargetData>();
	size = td.getTypeSizeInBits( argType );
	preArgs[2] = ConstantInt::get(Type::getInt32Ty(context), size ); 
	preArgs[3] = args[3];
	//preArgs[4] = args[4];// appName
	Value* preBranchVal;
	DEBUG( errs()<<"Inserting call to preFunc() :" <<*preFunc<<"\n" );
	if (preFunc!=NULL)
		preBranchVal = CallInst::Create(preFunc, preArgs.begin(), preArgs.end(), "preCond", entryBlock ); // Call for prefix function
	else	
		preBranchVal = ConstantInt::getTrue(context);
	BasicBlock* injectBlock = BasicBlock::Create(context,"inject", f );	

//// added by Jiesheng
  AllocaInst *tmploc = new AllocaInst(argType, 
                              ConstantInt::get(Type::getInt32Ty(context), 0),
                              "tmploc", entryBlock);
  new StoreInst(args[2], tmploc, entryBlock);




	BasicBlock* exitBlock = BasicBlock::Create(context,"exit", f );
	//if pre condition is true, goto inject function
	BranchInst::Create( injectBlock, exitBlock, preBranchVal, entryBlock );		
	BranchInst *bi2 = BranchInst::Create(  exitBlock ,injectBlock);
	string preStr("pre-injection");
	// Insert call to injection function
	DEBUG( errs()<<"Inserting call to injectFunc() :" <<*injectFunc<<"\n" );
	//vector<Value*> injectArgs(3);
	vector<Value*> injectArgs(5); // Qining, add one more argument for bit_byte_whole_flag, Jiesheng added one more
	injectArgs[0] = args[0]; //FINumber

	injectArgs[1] = preArgs[1]; // the ENUM
	injectArgs[2] = preArgs[2]; // The size
	injectArgs[3] = preArgs[3]; // Qining, add one more argument for bit_byte_whole_flag
  
  //Jiesheng
  injectArgs[4] = new BitCastInst(tmploc, 
                    PointerType::get(Type::getInt8Ty(context), 0), "tmploc_cast", bi2);


	CallInst::Create( injectFunc, injectArgs.begin(),injectArgs.end(), "", bi2); 	// Insert the inject call before the branch instruction to exit block
	
  //Jiesheng
  LoadInst *updateval = new LoadInst(tmploc, "updateval", exitBlock);
  
  // changed from args[2] to updateval by Jiesheng
  ReturnInst::Create(context,updateval, exitBlock );		// create a return instruction at the end of the block
}

void FaultInjectionRandom::createInjectionFunctions(Module* m) {
	
	vector<const Type*> argTy(4); // Qining, add one more argument for bit_byte_whole_flag
	LLVMContext& context = m->getContext();
	argTy[0] = Type::getInt32Ty(context);
	argTy[1] = Type::getInt32Ty(context);
	argTy[2] = Type::getInt32Ty(context);
	argTy[3] = Type::getInt32Ty(context); // Qining, add one more argument for bit_byte_whole_flag//argTy[4] = PointerType::get(Type::getInt8Ty(context),0);
	
  // Jiesheng
  vector<const Type*> fiargsTy(5);
  fiargsTy[0] = argTy[0]; fiargsTy[1] = argTy[1]; 
  fiargsTy[2] = argTy[2]; fiargsTy[3] = argTy[3];
  fiargsTy[4] = PointerType::get(Type::getInt8Ty(context), 0);


  FunctionType* injectFuncType = FunctionType::get(Type::getVoidTy(context), fiargsTy, 0);
	FunctionType* preFuncType = FunctionType::get(Type::getInt1Ty(context), argTy, 0); 
	DEBUG( cerr<<"Inserting fault-injection function into module\n");
	Constant* injectFunc = m->getOrInsertFunction("injectFunc", injectFuncType);			// get the injection function
	Constant* preFunc = m->getOrInsertFunction("preFunc", preFuncType);	// get the pre-injection function
	for (map<const Type*, string>::iterator fi = FiFuncName.begin(), fe = FiFuncName.end(); fi!=fe; ++fi) {
		const Type* fiType = fi->first;
		string fiName = fi->second;
		createInjectionFunc(m, fiType, fiName, injectFunc, preFunc);
	}
}

// Print fault-indices to the index file
void FaultInjectionRandom::printFaultIndices(Module *M) {
	
    const string moduleName = M->getModuleIdentifier();
    ofstream indexFile;					// File containing indices of instructions

    indexFile.open((moduleName + string(".fault-index.txt")).c_str(), ios::out);

    for (map<Instruction*, Instruction*>::iterator mi = FaultIndexMap.begin(), me = FaultIndexMap.end(); mi!=me; ++mi) {
	    Instruction* fi = (*mi).second;
	    indexFile<<fi->getNameStr();
	    indexFile << "\t[ ";
	    for (Instruction::use_iterator ui = fi->use_begin(), ue = fi->use_end(); ui!=ue; ++ui) {
		    Value* uv = *ui;
		    if ( Instruction* UI = dyn_cast<Instruction>(uv) ) {
			    if (FaultIndexMap.find(UI)!= FaultIndexMap.end() ) {
				    Instruction* useFi = FaultIndexMap[UI];
				    indexFile << "'" << useFi->getNameStr() << "', ";
			    }		
		    }
	    }
	    indexFile << " None ]";
	    indexFile<<"\n";
    }
    indexFile.close();
}

void FaultInjectionRandom::getStaticInstances()
{
	uint64_t finumber;
	CmpInst *ci;
	for (map<Instruction*, Instruction*>::iterator mi = FaultIndexMap.begin(), me = FaultIndexMap.end(); mi!=me; ++mi) 
	{
		Instruction* I = (*mi).first;
		Instruction* fi = (*mi).second;
		finumber = getStaticId(fi);
		if((int)finumber == -1)
		{	
			errs() << "Badly formed fault injection func\n";
			continue; 
		}
		else if(!(ci = dyn_cast<CmpInst>(I)))
			continue;
		//check if I is valid for branch or data instances
		is_branch_or_datavar(I,fi);
	}
}
bool FaultInjectionRandom::is_used_by_branch(Instruction *I)
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
bool FaultInjectionRandom::runOnFunction(Function &F)
{
    set<Instruction*> injectSet;
	//int is_used_by_branch = 0;
    for (inst_iterator fi = inst_begin(&F), fe = inst_end(&F); fi!=fe; ++fi) {
	    Instruction* I = &*fi;
		  if(!fioption.compare(onlybranch)){
			if(!isa<CmpInst>(I))
				continue;
			if(is_used_by_branch(I))
				injectSet.insert(I);
			continue;
		  }
		  //for injection into all instructions except invoke instructions (these are same as unconditional branch instructions with exception handling mechanism)
		  if(!isa<InvokeInst>(I))
			injectSet.insert(I);
    }
    insertInjectionFunc(injectSet, F.getParent()); // Insert code to inject faults for the instructions checked in function
	
    return true;
}

bool FaultInjectionRandom::doInitialization(Module &M)
{
	DEBUG(cerr<<"Calling doInitialization for Module " << M.getModuleIdentifier() << "\n");
	faultIndex =0;
	if(fioption.empty())
	{	errs() << "fioption not set\n"; }
	const string moduleName = M.getModuleIdentifier();
	Filenamebranch = moduleName+".branchstatic.txt";
	Filenamedatavar = moduleName+".datastatic.txt"; 
	branchstaticfile.open(Filenamebranch.c_str(),ios::out);
	datavarstaticfile.open(Filenamedatavar.c_str(),ios::out);
	if(!branchstaticfile.is_open())
	{ errs() <<"cannot open " << Filenamebranch << "\n";	return false; }
	if(!datavarstaticfile.is_open())
	{ errs() <<"cannot open " << Filenamedatavar << "\n";	return false; }

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
				map_func_argu[func_name] = vector< pair<unsigned int, int> >(); // creat entry
				
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
								int fault_type = BIT_FAULT;
								if(arg_set.find("<BYTE>") < arg_set.length())	fault_type = BYTE_FAULT;
								else if(arg_set.find("<WHOLE>") < arg_set.length())	fault_type = WHOLE_FAULT;
								unsigned int arg_num = atoi(arg.c_str()) - 1;
								map_func_argu[func_name].push_back(make_pair(arg_num, fault_type));
								std::cout << "\tinclude arg: " << map_func_argu[func_name].back().first + 1<<" type: "<<map_func_argu[func_name].back().second << "\n";
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

	bit_byte_whole_flag = 0;
	//***********************************************************************************************************

	return FunctionPass::doInitialization(M);	

}

bool FaultInjectionRandom::doFinalization(Module &M)
{
    const string moduleName = M.getModuleIdentifier();
	LLVMContext& context = M.getContext();
	Function* mainFunc = M.getFunction("main");
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
		Constant *initfunc =  M.getOrInsertFunction("initInjections", initInjectionFuncType);
		CallInst::Create(initfunc, initInjectArgs.begin(),initInjectArgs.end(), "", entryBlock->getFirstNonPHI() );
	
	    //Add the postInjections() function to close activation file
		BasicBlock *exitBlock = &mainFunc->back();
		FunctionType *postInjectionFuncType = FunctionType::get(Type::getVoidTy(context),0); 
		if(exitBlock)
		{
		Constant *postFunc = M.getOrInsertFunction("postInjections", postInjectionFuncType);
		CallInst::Create(postFunc, "",exitBlock->getTerminator());
		}
	}
	// Create the fault-injection functions
	createInjectionFunctions( &M );


  // Jiesheng
  errs() << "Pointer Instruction Number: " << ptrinstnum << "\n";
  errs() << "Cmp Instruction Number: " << cmpinstnum << "\n";
  errs() << "Total Instruction Number: " << totalinstnum << "\n";



	if(!fioption.compare(onlybranch))
		return FunctionPass::doFinalization(M);	
	// Print the list of instructions that are involved in the checks
	printFaultIndices(&M); 
	//get the static instances for branches and data
	getStaticInstances();
	branchstaticfile.close();
	datavarstaticfile.close();

	return FunctionPass::doFinalization(M);
}

Instruction* FaultInjectionRandom::insertPrintStatement(string& checkStr, Value* printVal, Instruction* I) {
	// DEBUG( cerr<<"Inserting print statement \n" );
	Module* M = I->getParent()->getParent()->getParent();	// Get the module corresponding to the duplciate pass
	LLVMContext& context = M->getContext();
	const int ty = printVal->getType()->getTypeID();	// Get the type ID of the vale to be printed
	string nameStr;
	//const string &modulename = M->getModuleIdentifier();
	if (printVal->hasName() ) 
		nameStr = printVal->getName();			// Get the name of the value to be printed
	else
		nameStr = "anonymous";
	string formatSpec;						// Choose the format specifier depending on the value type
	switch (ty) { 
		case Type::IntegerTyID: formatSpec = "%d"; break; 
		case Type::FloatTyID:
		case Type::DoubleTyID: formatSpec = "%f"; break;
		case Type::VectorTyID:
		case Type::ArrayTyID: formatSpec = "%s"; break;
		case Type::PointerTyID: formatSpec = "%p"; break;
		default: formatSpec = "%u";	// Don't know what type to assign here !
	}
	Function* printFunc = M->getFunction("printf");		// Get the function printf
	assert( printFunc!=NULL && "printf function not found!");
	string str = checkStr + string("\t") + nameStr + string(" = ") + formatSpec + string("\n");	// Make the format string ( name = value )
	Constant* Init = ConstantArray::get(context,str,true);				// Convert it to a LLVM Type
	GlobalVariable* fmtStr = new GlobalVariable(Init->getType(), true, GlobalValue::InternalLinkage, Init, "printStr." + nameStr);	
	M->getGlobalList().push_back( fmtStr );						// Insert it into the list of globals for module
	std::vector<Constant*>IndicesC(2);
	IndicesC[0] = Constant::getNullValue(Type::getInt32Ty(context));
	IndicesC[1] = ConstantInt::get(Type::getInt32Ty(context),0);

	Constant *getElemExpr =  ConstantExpr::getGetElementPtr(fmtStr, &IndicesC[0],IndicesC.size());
	vector<Value*> printArgs;			// Vector containing the arguments of the printf function
	printArgs.push_back( getElemExpr );		// Arg 1: format string
	printArgs.push_back( printVal );		// Arg 2: Value to be printed
	// Create a call to the printf function with the arguments
	CallInst* ci = CallInst::Create( printFunc, printArgs.begin(),printArgs.end(), "debug", I ); 
	return ci;
}
 
bool FaultInjectionRandom::is_branch_or_datavar(Instruction *I, Instruction *fi)
{
	//see if cmp instruction has conditional branch as use .. then add to branch file and add the FI of its defs to the datafile
	CmpInst *ci = dyn_cast<CmpInst>(I);
	if(!ci)
		return false;
	int is_used_by_branch = 0;    
	BranchInst *bi;
	for (Value::use_iterator i = fi->use_begin(), e = fi->use_end(); i != e; ++i)
	{
		Instruction *use = dyn_cast<Instruction>(*i);
		bi = dyn_cast<BranchInst>(use);
		if(!bi)
			continue;
		if(bi->isConditional())
		{	is_used_by_branch = 1; break; }

	}
	if(!is_used_by_branch)
		return false;
	if(!fioption.compare(nobranch))
		return true;
// 	errs() << *fi << "\t" <<*bi << "\n";
	int faultindex = getStaticId(fi);
	if(faultindex == -1)
		errs() <<"bad fi index! \n"; 
	branchstaticfile << faultindex << "\n";
	for (User::op_iterator i = I->op_begin(), e = I->op_end(); i != e; ++i) 
	{    
		Instruction *v = dyn_cast<Instruction>(*i);
		if(!v)
			continue;
		int staticid = getStaticId(v);
		if(staticid == -1)
		{	errs() << *v <<"\n"; errs() << *I<<"\n"; errs() << "Badly formed fault injection hook bc file!\n"; } 
		else
			datavarstaticfile << staticid <<"\n";//<<";inst="<< *v << "\n"; //write the static id of fault injection to the analysis file
	}
	return true;
}
uint64_t FaultInjectionRandom::getStaticId(Instruction *I)
{
	if(is_injectFaultFuncCall(I))
	{
		CallInst *ci = dyn_cast<CallInst>(I);
		Value *faultindex = ci->getArgOperand(0); 
		ConstantInt *cint = cast<ConstantInt>(faultindex);
		uint64_t staticid = cint->getZExtValue();
		return staticid;
	}
	return -1;
}
bool FaultInjectionRandom::is_injectFaultFuncCall(Instruction *I)
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

bool FaultInjectionRandom::filter(Instruction *I)
{
	bit_byte_whole_flag = BIT_FAULT; //set flag to default
	if(map_func_argu.empty())	
		{
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
			//return (map_func_argu.count(func_called->getName()) > 0);
			//check function
			if(func_called==NULL)
			{
				//errs()<<"\nCall function pointer\n";
				return false;
			}
			if(!map_func_argu.count(func_called->getName()))	continue;
			//check argument
			unsigned int argu_i = 0;
			for(argu_i = 0; argu_i < callinst->getNumOperands(); argu_i++)
			{
				if(callinst->getOperand(argu_i) == I)	break;
			}
			if(argu_i == callinst->getNumOperands())	continue;
			//if the argument set is empty, all arguments are candidates for insertion
			if(searchArgument(func_called->getName(), argu_i) == -1 && !map_func_argu[func_called->getName()].empty())	continue;
			if(!map_func_argu[func_called->getName()].empty())
				bit_byte_whole_flag = map_func_argu[func_called->getName()][searchArgument(func_called->getName(), argu_i)].second;
			else
				bit_byte_whole_flag = BIT_FAULT;
			
			return true;
		}
		else
		{
			continue;
		}

	}
	// if instruction I should not be instrumented, we will be here.
	//errs()<<"instruction: "<< *I << "is not instrumented\n"; // TODO: remove this
	return false;
}

int FaultInjectionRandom::searchArgument(string func_name, int pos_in_argu_list)
{
	unsigned pos_in_vector = 0;
	for(pos_in_vector = 0; pos_in_vector < map_func_argu[func_name].size(); pos_in_vector++)
	{
		if(map_func_argu[func_name][pos_in_vector].first == pos_in_argu_list)	break;
	}
	if(pos_in_vector == map_func_argu[func_name].size())	pos_in_vector = -1;
	//printf("found %d at: %d\n",pos_in_argu_list,pos_in_vector);
	return pos_in_vector;
}

static RegisterPass<FaultInjectionRandom> X("FaultInjectionRandom", "FaultInjectionRandom Pass",false,false);
