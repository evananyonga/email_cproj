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

static SSL *tls_connect(int sock) {
    SSL_CTX *ctx;
    SSL *ssl;

    SSL_library_init();
    SSL_load_error_strings();

    ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        printf("Error: could not create SSL context\n");
        return NULL;
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        printf("Error: TLS handshake failed\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return NULL;
    }

    SSL_CTX_free(ctx); // Free the context after creating the SSL object
    return ssl;
}

static int smtp_send_command(SSL *ssl, const char *cmd, int expected_code) {
    char response[512];
    int code;

    SSL_write(ssl, cmd, strlen(cmd));
    SSL_read(ssl, response, sizeof(response) - 1);

    code = atoi(response);
    if (code != expected_code) {
        printf("Error: expected %d but got %d - %s\n", expected_code, code, response);
        return 0;
    }
    return 1;
}
