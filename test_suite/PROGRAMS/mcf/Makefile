## target
TARGET=MCF

## llvm root and clang
include ../Makefile.common

SRC_FILES = $(wildcard *.c)
OBJECTS = $(SRC_FILES:.c=.bc)
LINKED = $(TARGET).bc
LL_FILE = $(TARGET).ll

## other choice
default: all

all: $(LL_FILE)

$(LL_FILE): $(LINKED)
	$(LLVMDIS) $(LINKED) -o $@

$(LINKED): $(OBJECTS)
	$(LLVMLD) $(OBJECTS) -o $@

%.bc:%.c
	$(LLVMGCC) $(COMPILE_FLAGS) $< -c -o $@

clean:
	$(RM) -f *.bc *.ll *.bc
