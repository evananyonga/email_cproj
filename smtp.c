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

static int smtp_send(const Email *email) {
    int sock;
    SSL *ssl;
    char cmd[512];

    /* Phase 1: Establish TCP connection */
    sock = tcp_connect("smtp.gmail.com", "587");
    if (sock < 0) return 0;

    /* Phase 2: Upgrade TLS */
    ssl = tls_connect(sock);
    if (ssl == NULL) {
        close(sock);
        return 0;
    }

    /* Phase 3: SMTP Authentication and Sending (Dialogue) */
    const char *smtp_user = getenv("SMTP_USER");
    const char *smtp_pass = getenv("SMTP_PASS");

    if (smtp_user == NULL || smtp_pass == NULL) {
        printf("Error: SMTP_USER or SMTP_PASS not set\n");
        return 0;
    }

    smtp_send_command(ssl, "EHLO localhost\r\n", 250);
    smtp_send_command(ssl, "AUTH LOGIN\r\n", 334);

    // Base64 encode username and password here and send them
    snprintf(cmd, sizeof(cmd), "%s\r\n", smtp_user);
    smtp_send_command(ssl, cmd, 334);

    snprintf(cmd, sizeof(cmd), "%s\r\n", smtp_pass);
    smtp_send_command(ssl, cmd, 334);

    snprintf(cmd, sizeof(cmd), "MAIL FROM:<%s>\r\n", email->from);
    smtp_send_command(ssl, cmd, 250);

    snprintf(cmd, sizeof(cmd), "RCPT TO:<%s>\r\n", email->to);
    smtp_send_command(ssl, cmd, 250);

    snprintf(cmd, sizeof(cmd), "DATA\r\n", 334);
    
    snprintf(cmd, sizeof(cmd), 
        "From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s\r\n.\r\n", 
        email->from, email->to, email->subject, email->body);
    
    SSL_write(ssl, cmd, strlen(cmd));

    /* Phase 4: Teardown */
    smtp_send_command(ssl, "QUIT\r\n", 221);
    SSL_free(ssl);
    
    return 1;
}
