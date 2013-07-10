#ifndef LLFI_LIB_UTILS_H
#define LLFI_LIB_UTILS_H

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
