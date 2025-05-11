CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I$(HOME)/systemc-install/include
LDFLAGS = -L$(HOME)/systemc-install/lib -lsystemc
LDLIBPATH = LD_LIBRARY_PATH=$(HOME)/systemc-install/lib

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
