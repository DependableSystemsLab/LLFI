#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define BACKWARD_SLICE_TRACING 1
#define BACKWARD_SLICE_TRACING 1
#define BACKWARD_SLICE_TRACING 1
#define BACKWARD_SLICE_TRACING 1
// add as required!
//#define BRANCH_PROF 1
//#define DATA_PROF 1
//#define GOLDEN_RUN 1
//#define BACKWARD_SLICE_TRACING 1

//------------Fault type define-------------
#define BIT_FAULT 0
#define BYTE_FAULT 1
#define WHOLE_FAULT 2
//------------------------------------------
//#define NO_STDOUTPUT

//NOTE: type attribute in injectFunc and preFunc can be used for trace calls (writing to trace files, instead of fault injecting)
FILE *profilingFile;
FILE *branchstaticfile;
FILE *datastaticfile;
char profilingFileName[80];
char branchstaticFileName[80];
char datastaticFileName[80];

long branch_count =0;
long curr_count = 0;
long datavar_count = 0;
long bs_count = 0;
long inject_instance = 0;
int done_injection = 0;
char option[10];
long instance_count =0;

FILE *logFile;
FILE *activatedFile;
char activatedFileName[80];
char str[100];
int iter_count=0;
int instance=0;
int finally_injected =0;

void initInjections(char *appName)
{
	int i =0;
	logFile = stderr;
	strcpy(profilingFileName, appName);
    strcat(profilingFileName, ".prof.txt");
	strcpy(activatedFileName, appName);
	strcat(activatedFileName,".activatedFaults.txt");
    if ((profilingFile = fopen(profilingFileName,"r"))==NULL) {
		fprintf(stderr,"Unable to open profiling file %s\n", profilingFileName);
		return;	
	}
	if ((activatedFile = fopen(activatedFileName,"a"))==NULL) {
		fprintf(stderr,"Unable to open activated file %s\n", activatedFileName);
		return;	
	}

    //if more counts exist, add them here
	unsigned int seed;
	FILE* urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(int), 1, urandom);
	fclose(urandom);
	srand(seed);
#ifdef BRANCH_PROF
	fprintf(logFile,"reached here branch prof\n");
	fscanf(profilingFile, "BranchCount = %d\n", &branch_count);
	//instance_count = branch_count;
	inject_instance = rand()%branch_count + 1;
#endif 
#ifdef DATA_PROF	
	//data profiling
    fprintf(logFile,"reached here data profiling\n");
	fscanf(profilingFile, "DataVariableCount = %d\n", &datavar_count);
	inject_instance = rand()%datavar_count + 1;		
	#endif 

#ifdef BACKWARD_SLICE_TRACING	
	fscanf(profilingFile, "BackwardSliceCount = %d\n", &bs_count);
	//inject_instance = rand()%bs_count + 1;	
	inject_instance = random() / (RAND_MAX * 1.0) * bs_count +1;
#endif	
	
	fclose(profilingFile);
}

//br and data are defined according to the static instances
int preFunc(int faultIndexNum, int type, int size, int bit_byte_whole_flag)
{
	if(!done_injection)
	{
		curr_count++;
		if(curr_count == inject_instance)
		{ 	done_injection = 1;
			return 1;
		}
	}
	return 0;
}
//each integer is 4 bytes (64 bit machine) ... offset is 3 ints + 1
void injectFunc(int id, int type, int size, int bit_byte_whole_flag) 
{
	unsigned char buf[1], bytepos, bitpos,single_bit;
	unsigned char errorbuf[8];
	int offset = 25, size_byte,i;

#ifdef __LP64__
	offset = 25;
// 64-bit code
#else
	offset = 77;
// 32-bit code
#endif
	/*for(myi = 0; myi<100; myi++)
	{
		printf("%d:\t%d\n",myi,buf[myi]);
	}*/
	
	if(size == 1) //1 bit --> branch result injection
	{
	  	//insert this branch id into the file... next injection is into the defs of this branch. 
	  	single_bit = buf[offset];
	  	buf[offset] ^= 0x1;
	#ifndef NO_STDOUTPUT
    	fprintf(logFile, "id:count = %d:%d\n", id, curr_count);
	  	fprintf(logFile, "Injected Fault : ID = %d\tsize = %d\told=0x%x\tnew=0x%x\tcount=%d\n", id, size, single_bit, buf[offset],curr_count);
	#endif
	 	fprintf(activatedFile, "Injected Fault : ID = %d\tsize = %d\told=0x%x\tnew=0x%x\tcount=%d\n", id, size, single_bit, buf[offset],curr_count);
	 	fflush(activatedFile); // flush the buffer of stdout, print into activated fault file even it crashes later.
	}
	else //data var injection
	{     
		size_byte = size/8;
	  	bytepos = random() / (RAND_MAX * 1.0) * size_byte;
	  	bitpos = random() / (RAND_MAX * 1.0) * 8;
	  
    	//fprintf(logFile, "id:count = %d:%d\n", id, curr_count);
	  	memcpy(errorbuf, &buf[offset], size_byte);
	  	switch(bit_byte_whole_flag)
	  	{
	  		case BIT_FAULT:
	  			errorbuf[ bytepos ] = errorbuf[ bytepos ] ^ (0x1 << bitpos);
	  			break;
	  		case BYTE_FAULT:
	  			errorbuf[ bytepos ] = (char)random();
	  			break;
	  		/*case WHOLE_FAULT:
	  			for(i = 0; i < size_byte; i++)
	  			{
	  				errorbuf[i] = (char)random();
	  			}
	  			break;*/
	  		default:
	  			errorbuf[ bytepos ] = errorbuf[ bytepos ] ^ (0x1 << bitpos); // default: one bit flip. Fault in whole is not ready yet Qining
	  	}
	#ifndef NO_STDOUTPUT
	  	fprintf(logFile, "size_byte=%d\taddress=%p\tbytepos=%d\tbitpos=%d\told errorbuf = 0x%x\n", size_byte, &buf[offset],bytepos,bitpos, errorbuf[ bytepos ]);
	  	fprintf(logFile, "Injected Fault : ID = %d\tsize = %d\told=0x%x\tnew=0x%x\tcount=%ld\n", id, size, buf[offset + bytepos], errorbuf[bytepos], curr_count);
	#endif
		//printf("\nActivated!\n");
		activatedFile = fopen(activatedFileName,"a");
	  	fprintf(activatedFile, "Injected Fault : ID = %d\tsize = %d\told=0x%x\tnew=0x%x\tcount=%ld\n", id, size, buf[offset + bytepos], errorbuf[bytepos], curr_count);
	  	fflush(activatedFile); // flush the buffer of stdout, print into activated fault file even it meets a crash latter. Qining
	  	memcpy(&buf[offset], errorbuf, size_byte); // Overwrite the original value
	}
}

void postInjections()
{
	fclose(activatedFile); 
}

