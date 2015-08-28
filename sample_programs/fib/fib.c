#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv) {
	
	unsigned int fib0 = 0, fib1 = 1;
	unsigned int n = atoi(argv[1]);
	unsigned int result;	

	if (n == 0) {
		result = 0;
	} else if (n == 1) {
		result = 1;
	} else {
		int i;
		for (i = 0; i < n - 1; ++i) {
			if (i % 2 == 0) {
				fib0 += fib1;
				result = fib0;
			} else {
				fib1 += fib0;
				result = fib1;
			}
		}
	}

	printf("%u\n", result);
}
