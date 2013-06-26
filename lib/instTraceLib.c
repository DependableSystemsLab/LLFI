#include <stdio.h>
#include <stdlib.h>


void printInstTracer(long instID, int opcode, int size, char* ptr) {
	int i;
	printf("ID: %d\tOPCode: %d\tNumBytes: %d\t Value: ", instID, opcode, size);
	for (i=0;i<size;i++) {
		printf("%hhx", ptr[i]);
	}
	printf("\n");
}