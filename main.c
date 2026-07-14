#include <stdio.h>
#include <stdlib.h>
#include "email.h"
#include "transport.h"
#include "config.h"
#include "cli.h"

int main(int argc, char *argv[]) {
    Args *args;
    Email email;
    Config *config;
    char config_path[256];

    /* parse CLI arguments */
    args = parse_args(argc, argv);
    if (args == NULL) return 1;

    /* if help flag is set, exit after printing usage */
    if (args->help) {
        free_args(args);
        return 0;
    }

    /* load config */
    snprintf(config_path, sizeof(config_path), "%s/C/email_app/config", getenv("HOME"));

    config = load_config(config_path);
    if (config == NULL) {
        printf("Error loading config.  Aborting...\n");
        return 1;
    }

   /* merge - CLI overides config */
    email.from = config->smtp_from;
    email.to = config->smtp_to;
    email.subject = "Hello from your the other side";
    email.body = "Be Afraid, be very afraid.  I am coming for you.";

    if (!validate_email(&email)) {
        printf("Email is invalid.  Aborting...\n");
        free_config(config);
        return 1;
    }

    Transport *transport = get_transport(config->default_backend);
    if (transport == NULL) {
        printf("Error: No transport found for %s\n", config->default_backend);
        free_config(config);
        return 1;
    }

    // printf("DEBUG email from: %s\n", email.from ? email.from : "NULL");

    transport->send(&email, config);
    free_config(config);

    return 0;
}