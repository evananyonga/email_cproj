#include <stdio.h>
#include <stdlib.h>
#include "email.h"
#include "transport.h"
#include "config.h"

int main() {
    Email email;
    Config *config;
    char config_path[256];
    snprintf(config_path, sizeof(config_path), "%s/C/email_app/config", getenv("HOME"));

    config = load_config(config_path);
    if (config == NULL) {
        printf("Error loading config.  Aborting...\n");
        return 1;
    }

    print_config(config);

    email.from = config->smtp_user;
    email.to = config->smtp_user;
    email.subject = "Hello from your the other side";
    email.body = "Be Afraid, be very afraid.  I am coming for you.";

    if (!validate_email(&email)) {
        printf("Email is invalid.  Aborting...\n");
        free_config(config);
        return 1;
    }

    Transport *transport = get_transport("rest_api");
    if (transport == NULL) {
        printf("Error: No transport found for rest_api\n");
        free_config(config);
        return 1;
    }

    transport->send(&email, config);
    free_config(config);

    return 0;
}