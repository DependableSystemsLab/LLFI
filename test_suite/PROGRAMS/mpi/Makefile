## target
CLIENT=echoClient
SERVER=echoServer

## llvm root and clang
include ../Makefile.common

LINKED = $(CLIENT).bc $(SERVER).bc
LL_FILES = $(CLIENT).ll $(SERVER).ll

## other choice
default: all

all: $(LL_FILES)

%.ll: %.bc
	$(LLVMDIS) $< -o $@

%.bc:%.c
	$(LLVMGCC) $(COMPILE_FLAGS) $< -c -o $@

clean:
	$(RM) -f *.bc *.ll *.bc
