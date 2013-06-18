#include <stdio.h>
#include <stdlib.h>

void printInstProfile(long instID, const char* opcode, int numOps, int val0, int val1, int val2, int val3) {
	printf("ID: %d \tOPCode: %d \tNumOps: %d\tArg1: %d\tArg2: %d\tArg3: %d\tArg4: %d\t\n", instID, opcode, numOps, val0, val1, val2, val3);
}