#Compiler

CC = gcc

#flags
CFLAGS = -Wall -Werror -g

#out file
TARGET = tic_tac_toe

#source files
SRCS = tictactoe.c map.c

#object files
OBJS = $(SRCS:.c=.o)

# Default target, to compile the program
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
