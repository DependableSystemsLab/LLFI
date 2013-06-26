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