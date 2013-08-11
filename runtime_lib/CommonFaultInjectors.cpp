#include "FaultInjector.h"
#include "FaultInjectorManager.h"

class BitFlipFI: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] ^= 0x1 << fi_bitpos;
  }
};

class StuckAt0FI: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] &= ~(0x1 << fi_bitpos);
  }
};

class StuckAt1FI: public FaultInjector {
 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,
                      char *buf) {
    unsigned fi_bytepos = fi_bit / 8;
    unsigned fi_bitpos = fi_bit % 8;
    buf[fi_bytepos] |= 0x1 << fi_bitpos;
  }
};

static RegisterFaultInjector X("bitflip", new BitFlipFI());
static RegisterFaultInjector Y("stuck_at_0", new StuckAt0FI());
static RegisterFaultInjector Z("stuck_at_1", new StuckAt1FI());
