CC = gcc
CFLAGS = -Wall

# Find all .c files and generate corresponding .exe filenames
SRC = $(wildcard */*.c *.c)   # Finds all .c files in current directory and subdirectories
OBJ = $(SRC:.c=)               # Converts .c files to executable names by removing the .c extension

# Default target: Compile all .c files into executables
all: $(OBJ)

# Rule to compile each .c file into an executable (without the .exe extension)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up: Remove all executable files and .txt files
clean:
	rm -f $(OBJ) *.txt
