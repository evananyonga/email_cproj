#include <stdio.h>
#include <string.h>
#include "transport.h"
#include "sendmail.h"
#include "smtp.h"
#include "rest_api.h"

Transport *get_transport(const char *name) {    
    if (strcmp(name, "sendmail") == 0) {
        return &sendmail_transport;
    }
    if (strcmp(name, "smtp") == 0) {
        return &smtp_transport;
    }
    if (strcmp(name, "rest_api") == 0) {
        return &rest_api_transport;
    }
    printf("Error: Unknown Transport '%s' not found\n", name);
    return NULL; // Transport not found
}