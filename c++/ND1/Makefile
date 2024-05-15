# Compiler and compiler options
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Library and include paths
LIBS = -lgpiod -lgpiodcxx

# List of source files and corresponding binary names
SOURCES = $(wildcard ./*.cpp)
BINS = $(patsubst ./%.cpp,./%,$(SOURCES))

# Object files
OBJS = $(patsubst ./%.cpp,./%.o,$(SOURCES))

# Targets
all: $(BINS)

$(BINS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)


.PHONY: clean

clean:
	rm -rf $(OBJS) $(BINS)
