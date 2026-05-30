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
        printf("Error: could not resolve host %s:%s\n", host, port);
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
        ERR_print_errors_fp(stderr);
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
    memset(response, 0, sizeof(response));
    SSL_read(ssl, response, sizeof(response) - 1);

    code = atoi(response);
    if (code != expected_code) {
        printf("Error: expected %d but got %d - %s\n", expected_code, code, response);
        return 0;
    }
    return 1;
}

static void base64_encode(const char *input, char *output, size_t output_size) {
    // Implement base64 encoding
    const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0, j = 0, len = strlen(input);
    unsigned char buf[3];
    (void)output_size;
    
    while (len > 0) {
        int chunk_size = (len > 3) ? 3 : len;
        memset(buf, 0, sizeof(buf));
        memcpy(buf, input + i, chunk_size);

        output[j++] = table[buf[0] >> 2];
        output[j++] = table[((buf[0] & 0x03) << 4) | (buf[1] >> 4)];
        output[j++] = (chunk_size > 1) ? table[((buf[1] & 0x0F) << 2) | (buf[2] >> 6)] : '=';
        output[j++] = (chunk_size > 2) ? table[buf[2] & 0x3F] : '=';

        i += chunk_size;
        len -= chunk_size;
    }
}

static int smtp_send(const Email *email, const Config *config) {
    int sock;
    SSL *ssl;
    char cmd[512];

    /* Phase 1: Establish TCP connection */
    sock = tcp_connect("smtp.gmail.com", config->smtp_port);
    if (sock < 0) return 0;

    /* Phase 2: Upgrade TLS */
    ssl = tls_connect(sock);
    if (ssl == NULL) {
        // close(sock);
        return 0;
    }

    /* Phase 3: SMTP Authentication and Sending (Dialogue) */
    const char *smtp_user = config->smtp_user;
    const char *smtp_pass = config->smtp_password;

    char auth_plain[512];
    char auth_encoded[768];
    // int auth_len;

    if (smtp_user == NULL || smtp_pass == NULL) {
        printf("Error: smtp_user or smtp_pass not set\n");
        return 0;
    }

    char response[512];
    
    do {
        memset(response, 0, sizeof(response));
        SSL_read(ssl, response, sizeof(response) - 1);
    } while (strncmp(response, "220-", 4) == 0);

    /* EHLO localhost */
    smtp_send_command(ssl, "EHLO localhost\r\n", 250);

    // auth_len = snprintf(auth_plain, sizeof(auth_plain), 
    //                     "%c%s%c%s", 0, config->smtp_user, 0, config->smtp_password); 

    // Base64 encode username and password here and send them
    base64_encode(auth_plain, auth_encoded, sizeof(auth_encoded));

    snprintf(cmd, sizeof(cmd), "AUTH PLAIN %s\r\n", auth_encoded);
    smtp_send_command(ssl, cmd, 235);

    /* envelop */
    snprintf(cmd, sizeof(cmd), "MAIL FROM:<%s>\r\n", email->from);
    smtp_send_command(ssl, cmd, 250);

    snprintf(cmd, sizeof(cmd), "RCPT TO:<%s>\r\n", email->to);
    smtp_send_command(ssl, cmd, 250);

    /* message */
    smtp_send_command(ssl, "DATA\r\n", 354);

    snprintf(cmd, sizeof(cmd), 
        "From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s\r\n.\r\n", 
        email->from, email->to, email->subject, email->body);
    
    SSL_write(ssl, cmd, strlen(cmd));

    /* Phase 4: Teardown */
    smtp_send_command(ssl, "QUIT\r\n", 221);
    SSL_free(ssl);
    
    return 1;
}

Transport smtp_transport = {
    .name = "smtp",
    .send = smtp_send,
    .validate = NULL // Add validation logic if needed
};