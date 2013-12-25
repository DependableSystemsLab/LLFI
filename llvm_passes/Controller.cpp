#include "llvm/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include "Controller.h"
#include "FICustomSelectorManager.h"
#include "Utils.h"
#include "FIInstSelectorManager.h"
#include "FIInstSelector.h"
#include "InstTypeFIInstSelector.h"
#include "FuncNameFIInstSelector.h"
#include "FIRegSelector.h"
#include "RegLocBasedFIRegSelector.h"

using namespace llvm;

namespace llfi {
/**
 * Inject Instruction
 */
static cl::list< FIInstSelMethod > fiinstselmethod(
    cl::desc("Choose how to specify the fault injection target instructions"),
    cl::values(
      clEnumVal(insttype, "Specify through instruction type/opcode"),
      clEnumVal(funcname, "Specify through function name"),
      clEnumVal(sourcecode, "Specify through source code"),
      clEnumVal(custominstselector, 
                "Specify through custom instruction selector"),
      clEnumValEnd),
    cl::ZeroOrMore);

// inst type
static cl::list< std::string > includeinst("includeinst", 
    cl::desc("The type of instruction to be included for fault injection"), 
    cl::ZeroOrMore);
static cl::list< std::string > excludeinst("excludeinst", 
    cl::desc("The type of instruction to be excluded for fault injection"), 
    cl::ZeroOrMore);

// func name
static cl::list< std::string > includefunc("includefunc", 
    cl::desc("The function name to be included for fault injection"), 
    cl::ZeroOrMore);
static cl::list< std::string > excludefunc("excludefunc", 
    cl::desc("The function name to be excluded for fault injection"), 
    cl::ZeroOrMore);

// custom instruction selector name
static cl::opt < std::string > fiinstselectorname("fiinstselectorname",
    cl::desc("Custom fault injection instruction selector name"));

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
static cl::opt< FIRegSelMethod > firegselmethod(
    cl::desc("Choose how to specify the fault injection target registers"),
    cl::init(regloc),
    cl::values(
      clEnumVal(regloc, 
                "Specify through register location, e.g. dstreg, srcreg1."),
      clEnumVal(customregselector, "Specify through custom register selector"),
      clEnumValEnd));

static cl::opt< FIRegLoc > fireglocation(
    cl::desc("Choose fault injection register location:"),
    cl::init(dstreg),
    cl::values(
      clEnumVal(dstreg, "Inject into destination register"),
      clEnumVal(allsrcreg, "Inject randomly into one of all source registers"),
      clEnumVal(srcreg1, "Inject into 1st source register"),
      clEnumVal(srcreg2, "Inject into 2nd source register"),
      clEnumVal(srcreg3, "Inject into 3rd source register"),
      clEnumVal(srcreg4, "Inject into 4th source register"),
      clEnumValEnd));

static cl::opt < std::string > firegselectorname("firegselectorname",
    cl::desc("Custom fault injection register selector name"));

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
        errs() << "ERROR: Invalid include instruction type: " << includeinst[i]
            << "\n";
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
      errs() << "ERROR: Invalid exclude instruction type: " << excludeinst[i]
          << "\n";
      exit(1);
    }
  }
}
void Controller::getFuncList(std::set<std::string> *fi_func_set) {
  std::set<std::string>::iterator it;
  std::string func;
  for (size_t i = 0; i < includefunc.size(); ++i) {
    if(includefunc[i] == "all") {
      for(it = func_set.begin(); it != func_set.end(); ++it) {
        func = demangleFuncName(*it);
        fi_func_set->insert(func);
      }
    } else {
      func = demangleFuncName(includefunc[i]);
      fi_func_set->insert(func);
    }
  }

  // exclude list
  for(size_t i = 0; i < excludefunc.size(); ++i) {
    it = fi_func_set->find(excludefunc[i]);
    if(it != fi_func_set->end()) {
      fi_func_set->erase(it);
    } else {
      errs() << "ERROR: Invalid exclude function name: " << excludefunc[i]
          << "\n";
      exit(1);
    }
  }
}

void Controller::processInstSelArgs() {
  fiinstselector = new FIInstSelectorManager();
  std::set<unsigned> *fi_opcode_set;
  std::set<std::string> *fi_func_set;
  FICustomInstSelectorManager *m;
  for(size_t i = 0; i < fiinstselmethod.size(); ++i) {
    switch(fiinstselmethod[i]) {
      case insttype:
        fi_opcode_set = new std::set<unsigned>;
        getOpcodeListofFIInsts(fi_opcode_set);
        fiinstselector->addSelector(new InstTypeFIInstSelector(fi_opcode_set));
        break;
      case funcname:
        fi_func_set = new std::set<std::string>;
        getFuncList(fi_func_set);
        fiinstselector->addSelector(new FuncNameFIInstSelector(fi_func_set));
        break;
      case custominstselector:
        m = FICustomInstSelectorManager::getCustomInstSelectorManager();
        fiinstselector->addSelector(m->getCustomInstSelector(fiinstselectorname));
        break;
      default:
        // TODO: handle the source code case
        errs() << "ERROR: option not implemented yet\n";
        exit(4);
    }
  }
  fiinstselector->setIncludeBackwardTrace(includebackwardtrace);
  fiinstselector->setIncludeForwardTrace(includeforwardtrace);
}

void Controller::processRegSelArgs() {
  firegselector = NULL;
  if (firegselmethod == regloc) {
    firegselector = new RegLocBasedFIRegSelector(fireglocation);
  } else {
    FICustomRegSelectorManager *m = 
        FICustomRegSelectorManager::getCustomRegSelectorManager();
    firegselector = m->getCustomRegSelector(firegselectorname);
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

// Create a list of functions present in M. Certain care must be taken when
// compiling C++ due to name mangling.
void Controller::getModuleFuncs(Module &M) {
  Module::iterator it;
  for(it = M.begin(); it != M.end(); ++it) {
    std::string func_name = it->getNameStr();
    std::string final_name = demangleFuncName(func_name);

    func_set.insert(final_name);
  }
}

void Controller::init(Module &M) {
  // generate list of functions present in M
  getModuleFuncs(M);

  processCmdArgs();
  
  // select fault injection instructions
  std::set<Instruction*> fiinstset;
  fiinstselector->getFIInsts(M, &fiinstset);
  
  // select fault injection registers
  firegselector->getFIInstRegMap(&fiinstset, &fi_inst_regs_map);
}

Controller::~Controller() {
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
