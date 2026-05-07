# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g
# OpenSSL flags - adjust the path if OpenSSL is installed in a different location
LDFLAGS = -L/usr/local/opt/openssl/lib -lssl -lcrypto

# Files
TARGET = email
OBJS = main.o email.o transport.o sendmail.o

.PHONY: clean

# Default rule - build the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile each .c file to a .o object file
main.o: main.c email.h
	$(CC) $(CFLAGS) -c main.c

email.o: email.c email.h
	$(CC) $(CFLAGS) -c email.c

transport.o: transport.c transport.h
	$(CC) $(CFLAGS) -c transport.c

sendmail.o: sendmail.c sendmail.h
	$(CC) $(CFLAGS) -c sendmail.c

smtp.o: smtp.c smtp.h
	$(CC) $(CFLAGS) -c smtp.c

# Clean rule to remove all built files
clean:
	rm -f $(TARGET) $(OBJS)