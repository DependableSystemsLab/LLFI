## target
TARGET=bfs

## llvm root and clang
include ../Makefile.common
COMPILE_FLAGS += -fno-use-cxa-atexit

SRC_FILES = $(wildcard *.cpp)
OBJECTS = $(SRC_FILES:.cpp=.bc)
LINKED = $(TARGET).bc
LL_FILE = $(TARGET).ll

## other choice
default: all

all: $(LL_FILE)

$(LL_FILE): $(LINKED)
	$(LLVMDIS) $(LINKED) -o $@

$(LINKED): $(OBJECTS)
	$(LLVMLD) $(OBJECTS) -o $@

%.bc:%.cpp
	$(LLVMGCC) $(COMPILE_FLAGS) $< -c -o $@

clean:
	$(RM) -f *.bc *.ll *.bc
