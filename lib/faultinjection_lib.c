#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "utils.h"

static long long curr_cycle = 0;

static FILE *injectedfaultsFile;
static const unsigned OPTION_LENGTH = 512;

static int opcodecyclearray[OPCODE_CYCLE_ARRAY_LEN];
static bool is_fault_injected_in_curr_dyn_inst = false;

static struct {
  char fi_type[OPTION_LENGTH];
  bool fi_accordingto_cycle;
  // if both fi_cycle and fi_index are specified, use fi_cycle
  long long fi_cycle;
  long fi_index;

  // NOTE: the following config are randomly generated if not specified
  // in practice, use the following two configs only when you want to reproduce
  // a previous fault injection experiment
  int fi_reg_index;
  int fi_bit;
} config = {"bitflip", false, -1, -1, -1, -1}; 
// -1 to tell the value is not specified in the config file

// declaration of the real implementation of the fault injection function
void injectFaultImpl(const char *fi_type, long llfi_index, unsigned size,
                       unsigned fi_bit, char *buf);

/**
 * private functions
 */
void _initRandomSeed() {
  unsigned int seed;
	FILE* urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(int), 1, urandom);
	fclose(urandom);
	srand(seed);
}

// get whether to make decision based on probability
// return true at the probability of the param: probability
bool _getDecision(double probability) {
  return (rand() / (RAND_MAX * 1.0)) <= probability;
}

void _parseLLFIConfigFile() {
  char ficonfigfilename[80];
  strncpy(ficonfigfilename, "llfi.config.fi.txt", 80);
  FILE *ficonfigFile;
  ficonfigFile = fopen(ficonfigfilename, "r");
  if (ficonfigFile == NULL) {
    fprintf(stderr, "ERROR: Unable to open llfi config file %s\n",
            ficonfigfilename);
    exit(1);
  }

  const unsigned CONFIG_LINE_LENGTH = 1024;
  char line[CONFIG_LINE_LENGTH];
  char option[OPTION_LENGTH];
  char *value = NULL;
  while (fgets(line, CONFIG_LINE_LENGTH, ficonfigFile) != NULL) {
    if (line[0] == '#')
      continue;

    value = strtok(line, "=");
    strncpy(option, value, OPTION_LENGTH);
    value = strtok(NULL, "=");
    debug(("option, %s, value, %s;", option, value));

    if (strcmp(option, "fi_type") == 0) {
      strncpy(config.fi_type, value, OPTION_LENGTH);
      if (config.fi_type[strlen(config.fi_type) - 1] == '\n')
        config.fi_type[strlen(config.fi_type) - 1] = '\0';
    } else if (strcmp(option, "fi_cycle") == 0) {
      config.fi_accordingto_cycle = true;
      config.fi_cycle = atoll(value);
      assert(config.fi_cycle >= 0 && "invalid fi_cycle in config file");
    } else if (strcmp(option, "fi_index") == 0) {
      config.fi_index = atol(value);
      assert(config.fi_index >= 0 && "invalid fi_index in config file");
    } else if (strcmp(option, "fi_reg_index") == 0) {
      config.fi_reg_index = atoi(value);
      assert(config.fi_reg_index >= 0 && "invalid fi_reg_index in config file");
    } else if (strcmp(option, "fi_bit") == 0) {
      config.fi_bit = atoi(value);
      assert(config.fi_bit >= 0 && "invalid fi_bit in config file");
    } else {
      fprintf(stderr, 
              "ERROR: Unknown option %s for LLFI runtime fault injection\n",
              option);
      exit(1);
    }
  }
  debug(("type, %s; cycle, %lld; index, %ld; reg_index, %d; fi_bit, %d\n", 
         config.fi_type, config.fi_cycle, config.fi_index, 
         config.fi_reg_index, config.fi_bit));

  fclose(ficonfigFile);
}

/**
 * external libraries
 */
void initInjections() {
  _initRandomSeed();
  _parseLLFIConfigFile();
  getOpcodeExecCycleArray(OPCODE_CYCLE_ARRAY_LEN, opcodecyclearray);

  char injectedfaultsfilename[80];
  strncpy(injectedfaultsfilename, "llfi.stat.fi.injectedfaults.txt", 80);
  injectedfaultsFile = fopen(injectedfaultsfilename, "a");
  if (injectedfaultsFile == NULL) {
    fprintf(stderr, "ERROR: Unable to open injected faults stat file %s\n",
            injectedfaultsfilename);
    exit(1);
  }

  start_tracing_flag = TRACING_FI_RUN_INIT; //Tell instTraceLib that we are going to inject faults
}

bool preFunc(long llfi_index, unsigned opcode, unsigned my_reg_index, 
             unsigned total_reg_target_num) {
  assert(opcodecyclearray[opcode] >= 0 && 
          "opcode does not exist, need to update instructions.def");
  if (my_reg_index == 0)
    is_fault_injected_in_curr_dyn_inst = false;

  bool inst_selected = false;
  bool reg_selected = false;
  if (config.fi_accordingto_cycle) {
    if (config.fi_cycle >= curr_cycle && 
        config.fi_cycle < curr_cycle + opcodecyclearray[opcode])
      inst_selected = true;
  } else {
    // inject into every runtime instance of the specified instruction
    if (llfi_index == config.fi_index)
      inst_selected = true;
  }

  // each register target of the instruction get equal probability of getting
  // selected. the idea comes from equal probability of drawing lots
  if (inst_selected && (!is_fault_injected_in_curr_dyn_inst)) {
    // NOTE: if fi_reg_index specified, use it, otherwise, randomly generate
    if (config.fi_reg_index >= 0)
      reg_selected = (my_reg_index == config.fi_reg_index);
    else 
      reg_selected = _getDecision(1.0 / (total_reg_target_num - my_reg_index));

    if (reg_selected) {
      debug(("selected reg index %u\n", my_reg_index));
      is_fault_injected_in_curr_dyn_inst = true;
    }
  }

  if (my_reg_index == total_reg_target_num - 1)
    curr_cycle += opcodecyclearray[opcode];

  return reg_selected;
}

void injectFunc(long llfi_index, unsigned size, 
                char *buf, unsigned my_reg_index) {

  start_tracing_flag = TRACING_FI_RUN_FAULT_INSERTED; //Tell instTraceLib that we have injected a fault

  unsigned fi_bit, fi_bytepos, fi_bitpos;
  unsigned char oldbuf;

  // NOTE: if fi_bit specified, use it, otherwise, randomly generate
  if (config.fi_bit >= 0)
    fi_bit = config.fi_bit;
  else
    fi_bit = rand() / (RAND_MAX * 1.0) * size;
  assert (fi_bit < size && "fi_bit larger than the target size");
  fi_bytepos = fi_bit / 8;
  fi_bitpos = fi_bit % 8;
  
  memcpy(&oldbuf, &buf[fi_bytepos], 1);

  injectFaultImpl(config.fi_type, llfi_index, size, fi_bit, buf);

  debug(("FI stat: fi_type=%s, fi_index=%ld, fi_cycle=%lld, fi_reg_index=%u, "
         "fi_bit=%u, size=%u, old=0x%hhx, new=0x%hhx\n", config.fi_type,
            llfi_index, config.fi_cycle, my_reg_index, fi_bit, 
            size,  oldbuf, buf[fi_bytepos]));

  fprintf(injectedfaultsFile, 
          "FI stat: fi_type=%s, fi_index=%ld, fi_cycle=%lld, fi_reg_index=%u, "
          "fi_bit=%u\n", config.fi_type,
          llfi_index, config.fi_cycle, my_reg_index, fi_bit);
	fflush(injectedfaultsFile); 
}

void postInjections() {
	fclose(injectedfaultsFile); 
}
