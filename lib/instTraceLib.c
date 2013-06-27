#include <stdio.h>
#include <stdlib.h>

static int littleEndianness = -1;
int littleEndian() {
	int data;
	char *ptr;
	if (littleEndianness == -1) {
		data = 0x10000000;
		ptr = (char*)&data;
		/*int i;
		printf("Testing Endianness: ");
		for (i = 0; i<4; i++) {
			printf("%02hhx", ptr[i]);
		}
		printf("\n");*/
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

void printInstTracer(long instID, int opcode, int size, char* ptr) {
	int i;
	const char *TEST = "TEST";
	fprintf(OutputFile(TEST), "ID: %d\tOPCode: %d\tNumBytes: %d\t Value: ", instID, opcode, size);
	if (littleEndian()) {
		for (i=size-1; i>=0; i--) {
			fprintf(OutputFile(TEST), "%02hhx", ptr[i]);
		}
	} else {
		for (i=0; i<size; i++) {
			fprintf(OutputFile(TEST), "%02hhx", ptr[i]);
		}
	}
	fprintf(OutputFile(TEST), "\n");
	fflush(OutputFile(TEST)); //Program may crash before exit from main, must flush
							  //to ensure trace is outputted!
}