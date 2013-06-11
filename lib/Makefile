SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
AR = ar

all: libllfi.a

libllfi.a: $(OBJECTS)
	$(AR) rcs libllfi.a $^

clean:
	rm *.o *.a
