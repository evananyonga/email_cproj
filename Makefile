# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g

# Files
TARGET = email
OBJS = main.o email.o

.PHONY: clean

# Default rule - build the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile each .c file to a .o object file
main.o: main.c email.h
	$(CC) $(CFLAGS) -c main.c

email.o: email.c email.h
	$(CC) $(CFLAGS) -c email.c

# Clean rule to remove all built files
clean:
	rm -f $(TARGET) $(OBJS)