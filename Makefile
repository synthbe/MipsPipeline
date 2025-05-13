CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I$(SYSTEMC_PATH)/include
LDFLAGS = -L$(SYSTEMC_PATH)/lib -lsystemc
LDLIBPATH = LD_LIBRARY_PATH=$(SYSTEMC_PATH)/lib

SRC := $(wildcard src/*.cpp)
TESTS := $(wildcard test/*.cpp)
OBJS := $(patsubst test/%.cpp, build/test_%, $(TESTS))

build:
	mkdir -p build

build/test_%: test/%.cpp $(SRC) | build
	$(CXX) $(CXXFLAGS) $< $(SRC) $(LDFLAGS) -o $@

all: $(OBJS)

run-%: build/test_%
	$(LDLIBPATH) $<

clean:
	rm -rf build
