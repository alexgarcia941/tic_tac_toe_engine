# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -g -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lcriterion -pthread

# Directories
SRC_DIR = src
TEST_DIR = tests

# Target programs
TARGET = main_program
TEST_TARGET = test_runner

# Source files
MAIN_SRCS = $(SRC_DIR)/tictactoe.c $(SRC_DIR)/map.c
TEST_SRCS = $(SRC_DIR)/map.c $(TEST_DIR)/test_map.c

# Default target - Compile the main program
all: $(TARGET)

# Rule to compile the main program (no tests involved)
$(TARGET): $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRCS)

# Target for running the main program
run: $(TARGET)
	./$(TARGET)

# Target for compiling and running the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Rule to compile the tests (only builds the test executable)
$(TEST_TARGET): $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) $(LDFLAGS) 
# Clean target to remove compiled binaries
clean:
	rm -f $(TARGET) $(TEST_TARGET)

