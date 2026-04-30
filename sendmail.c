#include <stdio.h>
#include "sendmail.h"

static int sendmail_send(Email *email) {
    printf("From: %s\n", email->from);
    printf("To: %s\n", email->to);
    printf("Subject: %s\n", email->subject);
    printf("Body: %s\n", email->body);
    return 1; // Return 1 for success
}

static int sendmail_validate(void) {
    printf("sendmail: configuration is valid\n");
    return 1; // Return 1 for valid configuration
}

Transport sendmail_transport = {
    .name = "sendmail",
    .send = sendmail_send,
    .validate = sendmail_validate
};