# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g -I/usr/local/opt/openssl/include -I/usr/local/opt/curl/include
# OpenSSL flags - adjust the path if OpenSSL is installed in a different location
LDFLAGS = -L/usr/local/opt/openssl/lib -lssl -lcrypto -L/usr/local/opt/curl/lib -lcurl

# Files
TARGET = email
OBJS = main.o email.o transport.o sendmail.o smtp.o rest_api.o config.o

.PHONY: clean test

# Default rule - build the final binary
$(TARGET): test $(OBJS)
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

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

# Test Binary
test_email: test_email.o email.o
	$(CC) $(CFLAGS) test_email.o email.o -o test_email

test_config: test_config.o config.o
	$(CC) $(CFLAGS) test_config.o config.o -o test_config

test_email.o: test_email.c email.h
	$(CC) $(CFLAGS) -c test_email.c

test_config.o: test_config.c config.h
	$(CC) $(CFLAGS) -c test_config.c

test: test_email test_config
	./test_email
	./test_config

# Clean rule to remove all built files
clean:
	rm -f $(TARGET) $(OBJS) test_email.o test_email test_config.o test_config