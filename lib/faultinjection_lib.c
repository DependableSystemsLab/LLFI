#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "utils.h"

static FILE *ficonfigFile;
static FILE *logFile;
static FILE *activatedFile;

static int opcodecyclearray[OPCODE_CYCLE_ARRAY_LEN];
static bool is_fault_injected_in_curr_dyn_inst = false;

static long long curr_count = 0;

static struct {
  char faulttype[100];
  bool useficycle;
  long long fi_cycle;
  long fi_index;
  int fi_bit;
} config;


// private functions
bool _getDecision(double probability) {
  return (rand() / (RAND_MAX * 1.0)) <= probability;
}

void _parseLLFIConfigFile() {
  char ficonfigfilename[80];
  strcpy(ficonfigfilename, "llfi.fi.config.txt");

  ficonfigFile = fopen(ficonfigfilename, "r");
  if (ficonfigFile == NULL) {
    fprintf(stderr, "Unable to open llfi config file %s\n", ficonfigfilename);
    exit(1);
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
      strncpy(config.faulttype, value, 100);
    } else if (strcmp(option, "fi_cycle") == 0) {
      config.useficycle = true;
      config.fi_cycle = atol(value);
    } else if (strcmp(option, "fi_index") == 0) {
      config.fi_index = atol(value);
      config.useficycle = false;
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

  debug(("collected data, %s, %lld, %ld\n", config.faulttype, config.fi_cycle,
         config.fi_index));

  fclose(ficonfigFile);
}

// external libraries

void initInjections() {
  int i =0;
  logFile = stderr;
  unsigned int seed;
	FILE* urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(int), 1, urandom);
	fclose(urandom);
	srand(seed);

  _parseLLFIConfigFile();

  getOpcodeExecCycleArray(OPCODE_CYCLE_ARRAY_LEN, opcodecyclearray);

  char activatedfilename[80];
  strcpy(activatedfilename, "llfi.fi.activatedfaults.txt");
  activatedFile = fopen(activatedfilename, "a");
  if (activatedFile == NULL) {
    fprintf(stderr, "Unable to open activated file %s\n", activatedfilename);
  }
}

bool preFunc(long faultindex, unsigned opcode, unsigned my_reg_index, 
             unsigned total_reg_target_num) {
  assert(opcodecyclearray[opcode] >= 0 && 
          "opcode does not exist, need to update instructions.def");
  if (my_reg_index == 0)
    is_fault_injected_in_curr_dyn_inst = false;

  bool inst_selected = false;
  bool reg_selected = false;
  if (config.useficycle) {
    if (config.fi_cycle >= curr_count && 
        config.fi_cycle < curr_count + opcodecyclearray[opcode])
      inst_selected = true;
  } else {
    // inject into every runtime instance of the specified instruction
    if (faultindex == config.fi_index)
      inst_selected = true;
  }

  // each register target of the instruction get equal probability of getting
  // selected. the idea comes from equal probability of draw lots
  if (inst_selected && (!is_fault_injected_in_curr_dyn_inst)) {
    debug(("reg index %u\n", my_reg_index));
    reg_selected = _getDecision(1.0 / (total_reg_target_num - my_reg_index));
    if (reg_selected) {
      debug(("selected reg index %u\n", my_reg_index));
      is_fault_injected_in_curr_dyn_inst = true;
    }
  }

  if (my_reg_index == total_reg_target_num - 1)
    curr_count += opcodecyclearray[opcode];

  return reg_selected;
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
    bytepos = rand() / (RAND_MAX * 1.0) * size_byte;
    bitpos = rand() / (RAND_MAX * 1.0) * 8;
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

