#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "smtp.h"


static int tcp_connect(const char *host, const char *port) {
    struct addrinfo hints, *res;
    int sock;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port, &hints, &res) != 0) {
        printf("Error: could not resolve host %s:%s\n", host);
        return -1;
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        printf("Error: could not create socket\n");
        freeaddrinfo(res);
        return -1;
    }

if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        printf("Error: could not connect to %s:%s\n", host, port);
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);
    return sock;
}