#include <stdio.h>
#include <stdlib.h>

static int littleEndianness = -1;

int littleEndian() {
	int data;
	char *ptr;
	if (littleEndianness == -1) {
		data = 0x1000;
		ptr = (char*)&data;
		if (*ptr == 0x1) {
			littleEndianness = 0;
		}
		if (*ptr == 0x0) {
			littleEndianness = 1;
		}
	}
	return littleEndianness;
}

void printInstTracer(long instID, int opcode, int size, char* ptr) {
	int i;
	printf("ID: %d\tOPCode: %d\tNumBytes: %d\t Value: ", instID, opcode, size);
	if (littleEndian()) {
		for (i=size-1; i>=0; i--) {
			printf("%02hhx", ptr[i]);
		}
	} else {
		for (i=0; i<size; i++) {
			printf("%02hhx", ptr[i]);
		}
	}
	printf("\n");
}