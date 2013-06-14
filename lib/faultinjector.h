#ifndef FAULT_INJECTOR_H
#define FAULT_INJECTOR_H

class FaultInjector {
  // TODO: need to change the interface when we inject multiple bits faults
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) = 0;
};

#endif
