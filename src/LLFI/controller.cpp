#include <string>

#include "llvm/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#include "controller.h"
#include "utils.h"
#include "fiinstselector.h"
#include "insttypefiinstselector.h"
#include "firegselector.h"
#include "indexbasedfiregselector.h"

using namespace llvm;

namespace llfi {
/**
 * Inject Instruction
 */
// TODO: adding default values
static cl::opt< FIInstSelSrc > fiinstselsrc(
    cl::desc("Choose how to specify the fault injection target instructions"),
    cl::init(insttype),
    cl::values(
      clEnumVal(insttype, "Specify through instruction type/opcode"),
      clEnumVal(sourcecode, "Specify through source code"),
      clEnumVal(custominst, "Specify through custom function"),
      clEnumValEnd));

// inst type
static cl::list< std::string > includeinst("includeinst", 
    cl::desc("The type of instruction to be included for fault injection"), 
    cl::ZeroOrMore);
static cl::list< std::string > excludeinst("excludeinst", 
    cl::desc("The type of instruction to be excluded for fault injection"), 
    cl::ZeroOrMore);

// custom function
static cl::opt < std::string > fiinstselfunc("fiinstselfunc",
    cl::desc("Custom function name for fault injection instruction selection"));

// backtrace or forwardtrace included
static cl::opt< bool > includebackwardtrace("includebackwardtrace", 
  cl::init(false),
  cl::desc(
    "Include backward trace of the selected instructions for fault injection"));
static cl::opt< bool > includeforwardtrace("includeforwardtrace",
    cl::init(false),
    cl::desc(
     "Include forward trace of the selected instructions for fault injection"));

/**
 * Inject Register
 */
static cl::opt< FIRegSelSrc > firegselsrc(
    cl::desc("Choose how to specify the fault injection target registers"),
    cl::init(index),
    cl::values(
      clEnumVal(index, "Specify through register index, e.g. dstreg, srcreg1."),
      clEnumVal(customreg, "Specify through custom funtion"),
      clEnumValEnd));

static cl::opt< FIRegLoc > fireglocation(
    cl::desc("Choose fault injection location:"),
    cl::init(dstreg),
    cl::values(
      clEnumVal(dstreg, "Inject into destination register"),
      // TODO: disabled the option for now
      //clEnumVal(allsrcreg, "Inject into all source registers"),
      clEnumVal(srcreg1, "Inject into 1st source register"),
      clEnumVal(srcreg2, "Inject into 2nd source register"),
      clEnumVal(srcreg3, "Inject into 3rd source register"),
      clEnumVal(srcreg4, "Inject into 4th source register"),
      clEnumValEnd));

static cl::opt < std::string > firegselfunc("firegselfunc",
    cl::desc("Custom function name for fault injection register selection"));

/**
 * Log file
 */
cl::opt < std::string > llfilogfile("llfilogfile",
      cl::init("llfi.log.compilation.txt"),
      cl::Hidden,
      cl::desc("Name of compilation passes logging file"));


Controller *Controller::ctrl = NULL;

void Controller::getOpcodeListofFIInsts(std::set<unsigned> *fi_opcode_set) {
  NameOpcodeMap fullnameopcodemap;
  genFullNameOpcodeMap(fullnameopcodemap);

  // include
  for (unsigned i = 0; i != includeinst.size(); ++i) {
    // TODO: make "all" a static string
    if (includeinst[i] == "all") {
      for (NameOpcodeMap::const_iterator it = fullnameopcodemap.begin();
          it != fullnameopcodemap.end(); ++it) {
        fi_opcode_set->insert(it->second);  
      }
      break;
    } else {
      NameOpcodeMap::iterator loc = fullnameopcodemap.find(includeinst[i]);
      if (loc != fullnameopcodemap.end()) {
        fi_opcode_set->insert(loc->second);
      } else {
        errs() << "Invalid include instruction type: " << includeinst[i] << 
            "\n";
        exit(1);
      }
    }
  }

  // exclude
  for (unsigned i = 0; i != excludeinst.size(); ++i) {
    NameOpcodeMap::iterator loc = fullnameopcodemap.find(excludeinst[i]);
    if (loc != fullnameopcodemap.end()) {
      fi_opcode_set->erase(loc->second);
    } else {
      errs() << "Invalid exclude instruction type: " << excludeinst[i] << "\n";
      exit(1);
    }
  }
}

void Controller::processInstSelArgs() {
  fiinstselector = NULL;
  if (fiinstselsrc == insttype) {
    std::set<unsigned> *fi_opcode_set = new std::set<unsigned>;
    getOpcodeListofFIInsts(fi_opcode_set);
    fiinstselector = new InstTypeFIInstSelector(fi_opcode_set,
                                                includebackwardtrace,
                                                includeforwardtrace);
  } else if (fiinstselsrc == custominst) {
    // TODO: convert the function name to function 
  } else {
    // TODO: handle the source code case
  
  }
}

void Controller::processRegSelArgs() {
  firegselector = NULL;
  if (firegselsrc == index) {
    firegselector = new IndexBasedFIRegSelector(fireglocation);
  } else {
    // TODO: handle the custom case
  }
}

void Controller::processCmdArgs() {
  // clear the log file
  std::string err;
  raw_fd_ostream logFile(llfilogfile.c_str(), err, raw_fd_ostream::F_Append);
  if (err == "") {
    logFile << "\n\nStart of a pass\n";
  } else {
    errs() << "Unable to output logging information to file " << llfilogfile
        << "\n";
  }
  logFile.close();

  processInstSelArgs();
  processRegSelArgs();
}


void Controller::init(Module &M) {
  processCmdArgs();
  
  // select fault injection instructions
  std::set<Instruction*> fiinstset;
  fiinstselector->getFIInsts(M, &fiinstset);
  
  // select fault injection registers
  firegselector->getFIInstRegMap(&fiinstset, &fi_inst_regs_map);
}

Controller::~Controller() {
  delete fiinstselector;
  delete firegselector;
  delete ctrl;
  ctrl = NULL;
}

void Controller::dump() const {
  for (std::map<Instruction*, std::list< Value* > *>::const_iterator inst_it =
       fi_inst_regs_map.begin(); inst_it != fi_inst_regs_map.end(); ++inst_it) {
    errs() << "Selected instruction " << *(inst_it->first) << "\nRegs:\n";
    for (std::list<Value*>::const_iterator reg_it = inst_it->second->begin();
         reg_it != inst_it->second->end(); ++reg_it) {
      errs() << "\t" << **reg_it << "\n";
    }
    errs() << "\n";
  }
}

Controller *Controller::getInstance(Module &M) {
  if (ctrl == NULL)
    ctrl = new Controller(M);
  return ctrl;
}
}
