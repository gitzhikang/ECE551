# Makefile to compile Point, Circle, and main

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Executable name
TARGET = circles

# Source files
SRCS = main.cpp point.cpp circle.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Dependencies
Point.o: point.hpp
circle.o: circle.hpp point.hpp
main.o: point.hpp circle.hpp

.PHONY: all clean