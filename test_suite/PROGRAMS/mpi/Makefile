## target
CLIENT=echoClient
SERVER=echoServer

## llvm root and clang
include ../Makefile.common

LINKED = $(CLIENT).bc
LL_FILE = $(CLIENT).ll
EXE_FILE = $(SERVER).exe
## other choice
default: all

all: $(LL_FILE) $(EXE_FILE)

%.exe: %.c
	$(LLVMGCC) $< -o $@

%.ll: %.bc
	$(LLVMDIS) $< -o $@

%.bc:%.c
	$(LLVMGCC) $(COMPILE_FLAGS) $< -c -o $@

clean:
	$(RM) -f *.bc *.ll *.bc *.exe
