#include <stdio.h>
#include <string.h>
#include "transport.h"
#include "sendmail.h"

Transport *get_transport(const char *name) {    
    if (strcmp(name, "sendmail") == 0) {
        return &sendmail_transport;
    }
    printf("Error: Unknown Transport '%s' not found\n", name);
    return NULL; // Transport not found
}