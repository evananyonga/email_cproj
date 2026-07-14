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
    snprintf(config_path, sizeof(config_path), "%s/C/email_app/config", args->config_path ? args->config_path : getenv("HOME"));

    config = load_config(config_path);
    if (config == NULL) {
        free_args(args);
        printf("Error loading config.  Aborting...\n");
        return 1;
    }

   /* merge - CLI overides config */
    email.from = args->from ? args->from : config->smtp_from;
    email.to = args->to ? args->to : config->smtp_to;
    email.subject = args->subject ? args->subject : "(no subject)";
    email.body = args->body ? args->body : NULL;

    if (!validate_email(&email)) {
        printf("Email is invalid.  Aborting...\n");
        free_args(args);
        free_config(config);
        return 1;
    }

    /* select a transport backend based on CLI argument or config default */
    const char *backend = args->backend ? args->backend : config->default_backend;
    Transport *transport = get_transport(backend);
    if (transport == NULL) {
        printf("Error: No transport found for %s\n", backend);
        free_args(args);
        free_config(config);
        return 1;
    }

    // printf("DEBUG email from: %s\n", email.from ? email.from : "NULL");

    transport->send(&email, config);

    free_args(args);
    free_config(config);

    return 0;
}