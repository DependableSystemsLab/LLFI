#ifndef LLFI_LIB_UTILS_H
#define LLFI_LIB_UTILS_H

#define FIF_GOLDEN_RUN -1
#define FIF_FAULT_INSERTED 2
#define FIF_FAULT_INSERTED_AND_INIT 1
extern int faultInjectedFlag;

// assume the max opcode in instruction.def (LLVM) is smaller than 100
#define OPCODE_CYCLE_ARRAY_LEN 100
void getOpcodeExecCycleArray(const unsigned len, int *arr);

#define DEBUG
#ifdef DEBUG
#define debug(x) printf x; fflush(stdout);
#else
#define debug(x)
#endif

#endif
