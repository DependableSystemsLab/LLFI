#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "Utils.h"
#define OPTION_LENGTH 512
/*BEHROOZ 29 APRIL: We assume that the maximum number of fault injection locations is 100 when
it comes to multiple bit-flip model.*/
#define MULTIPLE_CYCLE_LENGTH 100
/*BEHROOZ MAY 2nd: This variable keeps track of the number of next_cycles*/
static int fi_next_cycles_count = 0;
//==============================================================

/*======================BEHROOZ @MAY 2nd============================
  I changed the below line to the current one to fix the fi_cycle===*/
static long long curr_cycle = 1; //static long long curr_cycle = 0;

static FILE *injectedfaultsFile;

static int fiFlag = 1;	// Should we turn on fault injections ?

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
  //======== Add number of corrupted bits QINING @MAR 13th========
  int fi_num_bits;
  //==============================================================
  //======== Add second corrupted regs QINING @MAR 27th===========
  long long fi_second_cycle;
  //==============================================================
  //======== Add multiple corrupted regs BEHROOZ @APRIL 29th======
  int fi_max_multiple; //JUNE 3rd
  long long fi_next_cycles[MULTIPLE_CYCLE_LENGTH];
  //==============================================================
} config = {"bitflip", false, -1, -1, -1, -1, 1, -1, -1, {-1}}; 
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
  strncpy(ficonfigfilename, "llfi.config.runtime.txt", 80);
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
  /*===============BEHROOZ @MAY 2nd==================*/
  int fi_next_cycles_index = 0;
  /*=================================================*/
  while (fgets(line, CONFIG_LINE_LENGTH, ficonfigFile) != NULL) {
    if (line[0] == '#')
      continue;

    value = strtok(line, "=");
    strncpy(option, value, OPTION_LENGTH);
    value = strtok(NULL, "=");

    //debug(("option, %s, value, %s;", option, value));

    if (strcmp(option, "fi_type") == 0) {
      strncpy(config.fi_type, value, OPTION_LENGTH);
      if (config.fi_type[strlen(config.fi_type) - 1] == '\n')
        config.fi_type[strlen(config.fi_type) - 1] = '\0';
    } else if (strcmp(option, "fi_cycle") == 0) {
      config.fi_accordingto_cycle = true;
      config.fi_cycle = atoll(value);
      /*======================BEHROOZ @MAY 2nd============================
        ===I changed the below line to the current one to fix the fi_cycle===*/
      assert(config.fi_cycle > 0 && "invalid fi_cycle in config file"); //assert(config.fi_cycle >= 0 && "invalid fi_cycle in config file");
    } else if (strcmp(option, "fi_index") == 0) {
      config.fi_index = atol(value);
      assert(config.fi_index >= 0 && "invalid fi_index in config file");
    } else if (strcmp(option, "fi_reg_index") == 0) {
      config.fi_reg_index = atoi(value);
      assert(config.fi_reg_index >= 0 && "invalid fi_reg_index in config file");
    } else if (strcmp(option, "fi_bit") == 0) {
      config.fi_bit = atoi(value);
      assert(config.fi_bit >= 0 && "invalid fi_bit in config file");
    //======== Add number of corrupted bits QINING @MAR 13th========
    } else if (strcmp(option, "fi_num_bits") == 0){
    	config.fi_num_bits = atoi(value);
    	assert(config.fi_num_bits >=0 && "invalid fi_num_bits in config file");
    //==============================================================	
    //======== Add second corrupted regs QINING @MAR 27th===========
    } else if (strcmp(option, "fi_second_cycle") == 0){
    	config.fi_second_cycle = atoll(value);
      /*======================BEHROOZ @MAY 2nd============================
        ===I changed the below line to the current one to fix the fi_cycle===*/        
    	assert(config.fi_second_cycle > 0 && "invalid fi_second_cycle in config file"); //assert(config.fi_second_cycle >= 0 && "invalid fi_second_cycle in config file");
    //==============================================================
    //==============================================================	
    //======== Add multiple corrupted regs BEHROOZ @APRIL 29th===========
    } else if (strcmp(option, "fi_max_multiple") == 0){
        assert(atoll(value) > 1 && "invalid fi_max_multiple in config file");
    	config.fi_max_multiple = atoi(value);
    } else if (strcmp(option, "fi_next_cycle") == 0){
    	assert(atoll(value) > 0 && "invalid fi_next_cycle in config file");
    	config.fi_next_cycles[fi_next_cycles_index] = atoll(value);
        fi_next_cycles_index++;
        fi_next_cycles_count = fi_next_cycles_index;
    //==============================================================
    } else {
      fprintf(stderr, 
              "ERROR: Unknown option %s for LLFI runtime fault injection\n",
              option);
      exit(1);
    }
  }
  /*
  debug(("type, %s; cycle, %lld; index, %ld; reg_index, %d; fi_bit, %d\n", 
         config.fi_type, config.fi_cycle, config.fi_index, 
         config.fi_reg_index, config.fi_bit));
  */
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
  
   if (! fiFlag) return false;
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
      //debug(("selected reg index %u\n", my_reg_index));
      is_fault_injected_in_curr_dyn_inst = true;
    }
  }

  if (my_reg_index == total_reg_target_num - 1)
    curr_cycle += opcodecyclearray[opcode];

  return reg_selected;
}

void injectFunc(long llfi_index, unsigned size, 
                char *buf, unsigned my_reg_index, unsigned reg_pos, char* opcode_str) {
  fprintf(stderr, "MSG: injectFunc() has being called\n");
  if (! fiFlag) return;
  start_tracing_flag = TRACING_FI_RUN_FAULT_INSERTED; //Tell instTraceLib that we have injected a fault

  unsigned fi_bit, fi_bytepos, fi_bitpos;
  unsigned char oldbuf;
  
  //======== Add opcode_str QINING @MAR 11th========
  unsigned fi_num_bits;
  fi_num_bits = config.fi_num_bits;
  char* score_board = (char*) calloc (size, sizeof(char));
  //================================================
  //======== Add opcode_str QINING @MAR 11th========
  int runs =0;
  /*======================BEHROOZ May 4th==========================
    We give value to fi_cycle_to_print because we want to make sure that the 
    fi_cycle that is printed in the for loop has the correct value when it 
    comes to cases where we want to both inject in more than one bit and also
    inject in more than one location.*/
  long long fi_cycle_to_print = config.fi_cycle;
  //================================================
  for(runs = 0; runs < fi_num_bits && runs < size; runs++){
  	  // NOTE: if fi_bit specified, use it, otherwise, randomly generate
	  if (config.fi_bit >= 0)
	    fi_bit = config.fi_bit;
	  else
	  {
	    //======== Add opcode_str QINING @MAR 11th========
	    do{
	    	fi_bit = rand() / (RAND_MAX * 1.0) * size;
	    }while(score_board[fi_bit] == 1);
	    score_board[fi_bit] = 1;
	    //================================================
	  }
	  assert (fi_bit < size && "fi_bit larger than the target size");
	  fi_bytepos = fi_bit / 8;
	  fi_bitpos = fi_bit % 8;
	  
	  memcpy(&oldbuf, &buf[fi_bytepos], 1);
	
	  //======== Add opcode_str QINING @MAR 11th========
	  /*======================BEHROOZ May 4th==========================*/
	  fprintf(injectedfaultsFile, 
          "FI stat: fi_type=%s, fi_index=%ld, fi_cycle=%lld, fi_reg_index=%u, "
          "fi_reg_pos=%u, fi_reg_width=%u, fi_bit=%u, opcode=%s", config.fi_type,
          llfi_index, fi_cycle_to_print, my_reg_index, reg_pos, size, fi_bit, opcode_str);
          if(config.fi_max_multiple !=-1)
          {
              fprintf(injectedfaultsFile, " fi_max_multiple=%u\n", config.fi_max_multiple);
          }
          else
          {
              fprintf(injectedfaultsFile, "\n");
          }
	  /*======================BEHROOZ May 4th==========================
           The below line is substituted with the above one as there was an 
           issue when we wanted to both inject in multiple bits and multiple
           locations.
           llfi_index, config.fi_cycle, my_reg_index, reg_pos, size, fi_bit, opcode_str);*/
	  //===============================================================
 	  fflush(injectedfaultsFile); 
	  //===============================================================
	  
	  //======== Add second corrupted regs QINING @MAR 27th===========
	  //update the fi_cycle to the fi_second_cycle,
	  // so later procedures can still use fi_cycle to print stat info
	  if(config.fi_second_cycle != -1)
	  {
	  	config.fi_cycle = config.fi_second_cycle;
	  	config.fi_second_cycle = -1;
	  }
          /*====Add multiple corrupted regs BEHROOZ @MAY 2nd===========*/
          else
          {
              long long next_cycle = -1;
              int index = 0;
              for(index = 0; index < fi_next_cycles_count && next_cycle == -1; index++)
              {
                   if(config.fi_next_cycles[index] != -1)
                   {
                        next_cycle = config.fi_next_cycles[index];
	                config.fi_cycle = next_cycle;
	  	        config.fi_next_cycles[index] = -1;
                   }                   
              }
          }
	  //==============================================================
  	  injectFaultImpl(config.fi_type, llfi_index, size, fi_bit, buf);
  }
  //==================================================
  /*
  debug(("FI stat: fi_type=%s, fi_index=%ld, fi_cycle=%lld, fi_reg_index=%u, "
         "fi_bit=%u, size=%u, old=0x%hhx, new=0x%hhx\n", config.fi_type,
            llfi_index, config.fi_cycle, my_reg_index, fi_bit, 
            size,  oldbuf, buf[fi_bytepos]));
*/
}

void turnOffInjections() {
	fiFlag = 0;
}

void turnOnInjections() {
	fiFlag = 1;
}

void postInjections() {
	fclose(injectedfaultsFile); 
}
