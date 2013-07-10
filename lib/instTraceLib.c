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

//Standard check for system endianness
//Optimized to only run after first call
static int littleEndianness = -1;
int littleEndian() {
	if (littleEndianness == -1) {
		int data;
		char *ptr;
		data = 0x10000000;
		ptr = (char*)&data; // 0x[10]000000 || //0x000000[10] in memory
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
		maxPrints = 1000;
	}
	
	//Faulty runs will begin with flag = 2, when the fault is detected it will set cutoff
	//instruction to current instruction + maxPrints
	if (faultInjectedFlag == 2) {
		faultInjectedFlag = 1;
		cutOff = instCount + maxPrints;
		//Print faulty trace header (for analysis by traceDiff script)
		fprintf(OutputFile(fname), "#Beginning Fault Trace at instruction: %d\n", instCount);
	}
	
	//These flags are set by faultinjection_lib.c (Faulty Run) or left initialized
	//in utils.c and left unchanged (Golden run)
	//faultInjectedFlag:
	//-1 = Golden Run
	//2 = fault inserted
	//1 = fault inserted (maxPrints set appropriately)
	//if maxPrints == 0 it will print trace info despite being over cutoff
	if ((faultInjectedFlag == -1) || ((faultInjectedFlag == 1) && ((instCount < cutOff) || (maxPrints == 0)))) {
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