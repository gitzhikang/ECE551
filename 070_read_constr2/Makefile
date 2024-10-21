
CXX = g++

CXXFLAGS = -Wall -g

TARGET = code

all: $(TARGET)

$(TARGET): code.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) code.o

code.o: code.cpp
	$(CXX) $(CXXFLAGS) -c code.cpp

clean:
	rm -f *.o $(TARGET)
