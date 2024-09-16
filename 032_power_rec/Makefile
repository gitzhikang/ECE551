# Variables
CC = gcc
CFLAGS = -Wall -g
OBJ = power.o test-power.o
TARGET = my_power

# Rule to build the final executable
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# Rule to compile power.c into power.o
main.o: power.c
	$(CC) $(CFLAGS) -c power.c -o power.o

# Rule to compile test-power.c into test-power.o
module.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c -o test-power.o

# Clean up the object files and executable
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
