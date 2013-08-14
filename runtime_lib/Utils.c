#include <stdio.h>
#include <assert.h>

#include "Utils.h"

int start_tracing_flag = TRACING_GOLDEN_RUN; //for instTraceLib: initialized to Golden Run setting

void getOpcodeExecCycleArray(const unsigned len, int *arr) {
  int i = 0;
  for (i = 0; i < len; ++i)
    arr[i] = -1;

#define HANDLE_INST(N, OPC, CLASS, CYCLE) \
  assert (N < len && "opcode execution cycle array too small");\
  arr[N] = CYCLE;
#include "Instruction.def"
}


bool isLittleEndian() {
  char *ptr;
  int data = 0x00000001;
  ptr = (char*)&data; 
  return *ptr == 0x1;
}
