C_SOURCES = $(wildcard *.c)
CXX_SOURCES = $(wildcard *.cpp)
C_OBJECTS = $(C_SOURCES:.c=.o)
CXX_OBJECTS = $(CXX_SOURCES:.cpp=.o)

OBJECTS = $(C_OBJECTS) $(CXX_OBJECTS)
#AR = ar

BUILDFLAGS = -fPIC

OS_NAME := $(shell uname -s)
ifeq ($(OS_NAME),Linux)
	TARGET = libllfi.so
	BUILDFLAGS += -shared
else
	ifeq ($(OS_NAME), Darwin)
		TARGET = libllfi.dylib
		BUILDFLAGS += -dynamiclib
	endif
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(BUILDFLAGS) -o $(TARGET) $^

clean:
	rm *.o $(TARGET)
