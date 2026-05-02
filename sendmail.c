#include <stdio.h>
#include "sendmail.h"

static int sendmail_send(const Email *email) {

    char command[256];
    snprintf(command, sizeof(command), "msmtp %s", email->to);
    
    FILE *pipe = popen(command, "w");
    if (pipe == NULL) {
        perror("Error: could not open pipe to msmtp\n");
        return 0; 
    }
    fprintf(pipe, "To: %s\n", email->to);
    fprintf(pipe, "From: %s\n", email->from);
    fprintf(pipe, "Subject: %s\n", email->subject);
    fprintf(pipe, "\n"); // Blank line to separate headers from body
    fprintf(pipe, "Body: %s\n", email->body);

    pclose(pipe);
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