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

static int littleEndianness = -1;
int littleEndian() {
	if (littleEndianness == -1) {
		int data;
		char *ptr;
		data = 0x10000000;
		ptr = (char*)&data;
		if (*ptr == 0x10) {
			littleEndianness = 0;
		}
		if (*ptr == 0x00) {
			littleEndianness = 1;
		}
	}
	return littleEndianness;
}

//Open a file for writing. This file is not explicitly closed, must flush often!
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
	//faultInjectedFlag
	int i;
	instCount++;

	if (maxPrints == -1) {
		maxPrints = 1000;
	}
	
	if (faultInjectedFlag == 2) {
		faultInjectedFlag = 1;
		cutOff = instCount + maxPrints;
		fprintf(OutputFile(fname), "#Beginning Fault Trace at instruction: %d\n", instCount);
	}
	
	if ((faultInjectedFlag == -1) || ((faultInjectedFlag == 1) && ((instCount <= cutOff) || (instCount == -1)))) {
		fprintf(OutputFile(fname), "ID: %d\tOPCode: %s\tValue: ", instID, opcode);
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