# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g -I/usr/local/opt/openssl/include -I/usr/local/opt/curl/include
# OpenSSL flags - adjust the path if OpenSSL is installed in a different location
LDFLAGS = -L/usr/local/opt/openssl/lib -lssl -lcrypto -L/usr/local/opt/curl/lib -lcurl

# Files
TARGET = email
OBJS = main.o email.o transport.o sendmail.o smtp.o rest_api.o

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

rest_api.o: rest_api.c rest_api.h
	$(CC) $(CFLAGS) -c rest_api.c

# Clean rule to remove all built files
clean:
	rm -f $(TARGET) $(OBJS)