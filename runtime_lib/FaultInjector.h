#include <string>

#ifndef FAULT_INJECTOR_H
#define FAULT_INJECTOR_H

class FaultInjector {
  // TODO: need to change the interface when we inject multiple bits faults
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) = 0;
  //virtual std::string getFaultInjectorType() = 0;
  virtual std::string getFaultInjectorType(){
		return std::string("Unknown");
	}
};

class HardwareFaultInjector: public FaultInjector {
	std::string getFaultInjectorType(){
		return std::string("HardwareFault");
	}
};

class SoftwareFaultInjector: public FaultInjector {
	std::string getFaultInjectorType(){
		return std::string("SoftwareFault");
	}
};

#endif
