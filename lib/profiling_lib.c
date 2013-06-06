#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <assert.h>

// assume the max opcode in instruction.def (LLVM) is smaller than 100
static long long opcodecount[100] = {0};

void doProfiling(int opcode) {
  assert(opcodecount[opcode] >= 0 && 
         "Dynamic instruction number too large to be handle");
  opcodecount[opcode]++;
}

void endProfiling() {
  FILE *profileFile;
  //TODO: have a central place to control the fault injection
  char profilefilename[80] = "llfi.prof.txt";
  profileFile = fopen(profilefilename, "w");
  if (profileFile == NULL) {
    fprintf(stderr, "Unable to open profiling file %s\n", profilefilename);
    return;	
  }

  unsigned i = 0;
  for (i = 0; i < 100; ++i) {
    if (opcodecount[i] > 0){	
      fprintf(profileFile, "opcode = %u, instnumber = %lld\n", 
              i, opcodecount[i]); 
    }
  }
	fclose(profileFile); 
}
