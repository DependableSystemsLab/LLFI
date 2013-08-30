#ifndef LLFI_LIB_UTILS_H
#define LLFI_LIB_UTILS_H

#include <stdbool.h>

// TRACING =  Tracing flag
#define TRACING_GOLDEN_RUN -1
#define TRACING_FI_RUN_INIT 0
#define TRACING_FI_RUN_FAULT_INSERTED 1
#define TRACING_FI_RUN_START_TRACING 2
extern int start_tracing_flag;

// assume the max opcode in instruction.def (LLVM) is smaller than 100
#define OPCODE_CYCLE_ARRAY_LEN 100
void getOpcodeExecCycleArray(const unsigned len, int *arr);

bool isLittleEndian();

#define DEBUG
#ifdef DEBUG
#define debug(x) printf x; fflush(stdout);
#else
#define debug(x)
#endif

#endif
