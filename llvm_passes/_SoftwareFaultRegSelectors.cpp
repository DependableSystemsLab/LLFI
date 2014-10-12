#include "_SoftwareFaultRegSelectors.h"

using namespace std;
namespace llfi {
    bool FuncArgRegSelector::isRegofInstFITarget(Value *reg, Instruction *inst){    
        if(isa<CallInst>(inst) == false){
            return false;
        }else{
            CallInst* CI = dyn_cast<CallInst>(inst);
            if(this->specified_arg == true){
                if(reg == CI->getArgOperand(this->pos_argument)){
                    return true;
                }else   return false;
            }else{
                for(int i = 0; i<CI->getNumArgOperands(); i++){
                    if(reg == CI->getArgOperand(i)) return true;
                }
                return false;
            }
        }
    }

    bool FuncDestRegSelector::isRegofInstFITarget(Value *reg, Instruction *inst){    
        if(isa<CallInst>(inst) == false){
            return false;
        }else{
            if(reg == inst) return true;
            else    return false;
        }
    }    

    bool RetValRegSelector::isRegofInstFITarget(Value *reg, Instruction *inst){ 
        if(isa<ReturnInst>(inst)){
            ReturnInst* RI = dyn_cast<ReturnInst>(inst);
            if(reg == RI->getReturnValue()) return true;
            else    return false;
        }else   return false;
    }

    static RegisterFIRegSelector A("FuncArgRegSelector", new FuncArgRegSelector());
    static RegisterFIRegSelector B("RetValRegSelector", new RetValRegSelector());
    static RegisterFIRegSelector C("FuncDestRegSelector", new FuncDestRegSelector());
}

 
