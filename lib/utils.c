#include <stdio.h>
#include <assert.h>

#include "utils.h"

void getOpcodeExecCycleArray(const unsigned len, int *arr) {
  int i = 0;
  for (i = 0; i < len; ++i)
    arr[i] = -1;

#define HANDLE_INST(N, OPC, CLASS, CYCLE) \
  assert (N < len && "opcode execution cycle array too small");\
  arr[N] = CYCLE;
#include "instruction.def"
}
