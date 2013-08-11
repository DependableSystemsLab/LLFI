/************
/instTraceLib.c
/Author: Sam Coulter
/  This library is part of the greater LLFI framework
/  This library should be linked against programs that have had the LLFI instTrace LLVM
/  pass performed on them
*************/

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

//Open a file (once) for writing. This file is not explicitly closed, must flush often!
static FILE* ofile = NULL;
FILE* OutputFile() {
  if (ofile == NULL) {
    ofile = fopen("llfi.stat.trace.txt", "w");
  }
  return ofile;
}

static long instCount = 0;
static long cutOff = 0;
void printInstTracer(long instID, char *opcode, int size, char* ptr, int maxPrints) {
  int i;
  instCount++;

  
  if (start_tracing_flag == TRACING_FI_RUN_FAULT_INSERTED) {
    start_tracing_flag = TRACING_FI_RUN_START_TRACING;
    cutOff = instCount + maxPrints;
    //Print faulty trace header (for analysis by traceDiff script)
    fprintf(OutputFile(), "#TraceStartInstNumber: %ld\n", instCount);
  }
  
  //These flags are set by faultinjection_lib.c (Faulty Run) or left 
  // initialized in utils.c and left unchanged (Golden run)
  if ((start_tracing_flag == TRACING_GOLDEN_RUN) || 
      ((start_tracing_flag == TRACING_FI_RUN_START_TRACING) && 
       (instCount < cutOff))) {
    fprintf(OutputFile(), "ID: %ld\tOPCode: %s\tValue: ", instID, opcode);
    
    //Handle endian switch
    if (isLittleEndian()) {
      for (i = size - 1; i >= 0; i--) {
        fprintf(OutputFile(), "%02hhx", ptr[i]);
      }
    } else {
      for (i = 0; i < size; i++) {
        fprintf(OutputFile(), "%02hhx", ptr[i]);
      }
    }
    fprintf(OutputFile(), "\n");
    fflush(OutputFile()); 
  }
}

void postTracing() {
  if (ofile != NULL)
    fclose(ofile);
}
