#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Utils.h"

static long long opcodecount[OPCODE_CYCLE_ARRAY_LEN] = {0};

void doProfiling(int opcode) {
  assert(opcodecount[opcode] >= 0 && 
         "dynamic instruction number too large to be handled by llfi");
  opcodecount[opcode]++;
}

void endProfiling() {
  FILE *profileFile;
  char profilefilename[80] = "llfi.stat.prof.txt";
  profileFile = fopen(profilefilename, "w");
  if (profileFile == NULL) {
    fprintf(stderr, "ERROR: Unable to open profiling result file %s\n", 
            profilefilename);
    exit(1);	
  }

  int opcode_cycle_arr[OPCODE_CYCLE_ARRAY_LEN];
  getOpcodeExecCycleArray(OPCODE_CYCLE_ARRAY_LEN, opcode_cycle_arr);

  unsigned i = 0;
  long long total_cycle = 0;
  for (i = 0; i < 100; ++i) {
    assert(total_cycle >= 0 && 
            "total dynamic instruction cycle too large to be handled by llfi");
    if (opcodecount[i] > 0) {	
      assert(opcode_cycle_arr[i] >= 0 && 
          "opcode does not exist, need to update instructions.def");
      total_cycle += opcodecount[i] * opcode_cycle_arr[i];
    }
  }

  fprintf(profileFile, "# do not edit\n");
  fprintf(profileFile, 
          "# cycle considered the execution cycle of each instruction type\n");
  fprintf(profileFile, "total_cycle=%lld\n", total_cycle);
	fclose(profileFile); 
}
