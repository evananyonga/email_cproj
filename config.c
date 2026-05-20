#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

Config *load_config(const char *path) {
    FILE *file;
    char line[256];
    Config *config;

    file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: Could not open config file '%s'\n", path);
        return NULL;
    }

    config = malloc(sizeof(Config));
    if (config == NULL) {
        printf("Error: Could not allocate memory for config\n");
        fclose(file);
        return NULL;
    }
    memset(config, 0, sizeof(Config)); // Initialize all char fields to NULL

    while (fgets(line, sizeof(line), file)) {
        char *key;
        char *value;
        char *equals;

        /* skip comments and blank lines*/
        // if (line[0] == '#' || line[0] == '\n') continue;
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        equals = strchr(line, '=');
        if (equals == NULL) continue;

        *equals = '\0';
        key = line;
        value = equals + 1;

        /* Remove trailing newline and space from key*/
        while (*key && (*key == ' ' || *key == '\t')) key++;
        char *end = equals - 1;
        while (end > key && (*end == ' ' || *end == '\t' || *end == '\n')) *end--  = '\0';

        /* Remove leading and trailing whitespace from value */
        while (*value && (*value == ' ' || *value == '\t')) value++;
        end = value + strlen(value) - 1;
        while (end > value && (*end == '\n' || *end == '\r' || *end == ' ')) *end-- = '\0';

        /* Allocate memory for the config values */
        if (strcmp(key, "default_backend") == 0) config->default_backend = strdup(value);
        else if (strcmp(key, "sendmail_path") == 0) config->sendmail_path = strdup(value);
        else if (strcmp(key, "smtp_host") == 0) config->smtp_host = strdup(value);
        else if (strcmp(key, "smtp_port") == 0) config->smtp_port = strdup(value);
        else if (strcmp(key, "smtp_user") == 0) config->smtp_user = strdup(value);
        else if (strcmp(key, "smtp_password") == 0) config->smtp_password = strdup(value);
        else if (strcmp(key, "smtp_tls") == 0) config->smtp_tls = strdup(value);
        else if (strcmp(key, "rest_provider_url") == 0) config->rest_provider_url = strdup(value);
        else if (strcmp(key, "rest_api_key") == 0) config->rest_api_key = strdup(value);
    }

    fclose(file);
    return config;
}

void free_config(Config *conf) {
    if (conf == NULL) return;

    free(conf->default_backend);
    free(conf->sendmail_path);
    free(conf->smtp_host);
    free(conf->smtp_port);
    free(conf->smtp_user);
    free(conf->smtp_password);
    free(conf->smtp_tls);
    free(conf->rest_provider_url);
    free(conf->rest_api_key);

    free(conf);
}

void print_config(Config *conf) {
    if (conf == NULL) {
        printf("Config is NULL\n");
        return;
    }

    printf("Config:\n");
    printf("  default_backend: %s\n", conf->default_backend ? conf->default_backend : "NULL");
    printf("  sendmail_path: %s\n", conf->sendmail_path ? conf->sendmail_path : "NULL");
    printf("  smtp_host: %s\n", conf->smtp_host ? conf->smtp_host : "NULL");
    printf("  smtp_port: %s\n", conf->smtp_port ? conf->smtp_port : "NULL");
    printf("  smtp_user: %s\n", conf->smtp_user ? conf->smtp_user : "NULL");
    printf("  smtp_password: %s\n", conf->smtp_password ? conf->smtp_password : "NULL");
    printf("  smtp_tls: %s\n", conf->smtp_tls ? conf->smtp_tls : "NULL");
    printf("  rest_provider_url: %s\n", conf->rest_provider_url ? conf->rest_provider_url : "NULL");
    printf("  rest_api_key: %s\n", conf->rest_api_key ? conf->rest_api_key : "NULL");
}