/************
/instTraceLib.c
/Author: Sam Coulter
/	This library is part of the greater LLFI framework
/	This library should be linked against programs that have had the LLFI instTrace LLVM
/	pass performed on them
*************/

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define DEFAULT_MAX_TRACES 1000

//Standard check for system endianness
//Optimized to only run after first call
static int littleEndianness = -1;
int littleEndian() {
	if (littleEndianness == -1) {
		int data;
		char *ptr;
		data = 0x10000000;
		ptr = (char*)&data; // Points to 0x[10]000000 or 0x[00]000010 in memory
		if (*ptr == 0x10) {
			littleEndianness = 0; //is big Endian
		}
		if (*ptr == 0x00) {
			littleEndianness = 1; //is little Endian
		}
	}
	return littleEndianness;
}

//Open a file (once) for writing. This file is not explicitly closed, must flush often!
static FILE* ofile = 0;
FILE* OutputFile(const char *name) {
	if (ofile == 0) {
		ofile = fopen(name, "w");
	}
	return ofile;
}

static long instCount = 0;
static int cutOff = 0;
void printInstTracer(long instID, char *opcode, int size, char* ptr, char* fname, int maxPrints) {
	int i; //General Counter
	instCount++;

	//Set Default maxPrints value if no value is specified
	if (maxPrints == -1) {
		maxPrints = DEFAULT_MAX_TRACES;
	}
	
	//Faulty runs will begin with flag = FIF_FAULT_INSERTED, when the fault is detected it will set cutoff
	//instruction to current instruction + maxPrints
	if (faultInjectedFlag == FIF_FAULT_INSERTED) {
		faultInjectedFlag = FIF_FAULT_INSERTED_AND_INIT;
		cutOff = instCount + maxPrints;
		//Print faulty trace header (for analysis by traceDiff script)
		fprintf(OutputFile(fname), "#TraceStartInstNumber: %d\n", instCount);
	}
	
	//These flags are set by faultinjection_lib.c (Faulty Run) or left initialized
	//in utils.c and left unchanged (Golden run)
	//if maxPrints == 0 it will print trace info despite being over cutoff
	if ( (faultInjectedFlag == FIF_GOLDEN_RUN) || 
		( (faultInjectedFlag == FIF_FAULT_INSERTED_AND_INIT) && 
		((instCount < cutOff) || (maxPrints == 0)) ) ) {
		fprintf(OutputFile(fname), "ID: %d\tOPCode: %s\tValue: ", instID, opcode);
		
		//Handle endian switch
		if (littleEndian()) {
			for (i=size-1; i>=0; i--) {
				fprintf(OutputFile(fname), "%02hhx", ptr[i]);
			}
		} else {
			for (i=0; i<size; i++) {
				fprintf(OutputFile(fname), "%02hhx", ptr[i]);
			}
		}
		fprintf(OutputFile(fname), "\n");
		
		fflush(OutputFile(fname)); //Program may crash before exit from main, must flush
								  //to ensure trace is outputted!	
	}

}