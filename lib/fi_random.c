#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>


static long long curr_count = 0;
#define DEBUG


#ifdef DEBUG
#define debug(x) printf x; fflush(stdout);
#else
#define debug(x)
#endif


static FILE *ficonfigFile;
static FILE *logFile;
static FILE *activatedFile;

static struct {
  char faulttype[100];
  bool usefiinstance;
  long long fi_instance;
  long fi_index;
  int fi_bit;
} config;

// TODO: currently assume all instructions take same number of cycles for
// execution, and one instruction has at most one register. If not, we need to
// have opcode and number of targets for one instruction included.

void parseLLFIConfigFile() {
  char ficonfigfilename[80];
  strcpy(ficonfigfilename, "llfi.fi.config.txt");

  ficonfigFile = fopen(ficonfigfilename, "r");
  if (ficonfigFile == NULL) {
    fprintf(stderr, "Unable to open llfi config file %s\n", ficonfigfilename);
    return;	
  }

  char line[1024];
  char option[100];
  char *value = NULL;
  while (fgets(line, 1024, ficonfigFile) != NULL) {
    if (line[0] == '#')
      continue;

    value = strtok(line, "=");
    strcpy(option, value);
    value = strtok(NULL, "=");

    debug(("option, %s, value, %s\n", option, value));

    if (strcmp(option, "faulttype") == 0) {
      strcmp(config.faulttype, value);
    } else if (strcmp(option, "fi_instance") == 0) {
      config.usefiinstance = true;
      config.fi_instance = atol(value);
    } else if (strcmp(option, "fi_index") == 0) {
      config.fi_index = atol(value);
      config.usefiinstance = false;
    } else if (strcmp(option, "fi_bit") == 0) {
      config.fi_bit = atoi(value);
      debug(("option, %s, value, %d\n", option, config.fi_bit));
    } else {
      fprintf(stderr, 
              "Unrecognized option %s for LLFI runtime fault injection\n",
              option);
      exit(1);
    }
  }

  debug(("collected data, %s, %lld, %ld", config.faulttype, config.fi_instance,
         config.fi_index));

  fclose(ficonfigFile);
}

void initInjections() {
  int i =0;
  logFile = stderr;

  parseLLFIConfigFile();

  char activatedfilename[80];
  strcpy(activatedfilename, "llfi.fi.activatedfaults.txt");
  activatedFile = fopen(activatedfilename, "a");
  if (activatedFile == NULL) {
    fprintf(stderr, "Unable to open activated file %s\n", activatedfilename);
    return;
  }
}

//br and data are defined according to the static instances
// TODO: change the parameter of size to opcode and make changes to passes
bool preFunc(long faultindex, int size) {
  if (config.usefiinstance) {
    curr_count++;
    if (curr_count == config.fi_instance) 
      return true;
  } else {
    if (faultindex == config.fi_index)
      return true;
  }
  return false;
}

void injectFunc(long faultindex, int size, char *buf) {
  unsigned char bytepos, bitpos, single_bit;
  unsigned char oldbuf;
  int size_byte, i;
	
  // TODO: add other fault type other than bit flip
  if(size == 1) {
    single_bit = buf[0];
    buf[0] ^= 0x1;
#ifdef DEBUG
    fprintf(logFile, 
            "Inject Fault: ID=%ld\tsize=%d\told=0x%x\tnew=0x%x\tcount=%lld\n",
            faultindex, size, single_bit, buf[0], curr_count);
#endif
    // TODO move the log to script after testing
    fprintf(activatedFile, 
            "Inject Fault: ID=%ld\tsize=%d\told=0x%x\tnew=0x%x\tcount=%lld\n", 
            faultindex, size, single_bit, buf[0], curr_count);
    fflush(activatedFile); 
	} else {
    // TODO: change the bit to be something specified by the config
    size_byte = size / 8;
    bytepos = random() / (RAND_MAX * 1.0) * size_byte;
    bitpos = random() / (RAND_MAX * 1.0) * 8;
    memcpy(&oldbuf, &buf[bytepos], 1);

	  buf[bytepos] = buf[bytepos] ^ (0x1 << bitpos);
#ifdef DEBUG
	  fprintf(logFile, 
            "Inject Fault: ID=%ld\tsize=%d\told=0x%x\tnew=0x%x\tcount=%lld\n",
            faultindex, size,  oldbuf, buf[bytepos], curr_count);
#endif
    fprintf(activatedFile, 
            "Inject Fault: ID=%ld\tsize=%d\told=0x%x\tnew=0x%x\tcount=%lld\n",
            faultindex, size,  oldbuf , buf[bytepos], curr_count);
	  	fflush(activatedFile); 
	}
  // TODO: change the log information later
}

void postInjections() {
	fclose(activatedFile); 
}

