#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

Config *load_config(const char *path) {
    FILE *file;
    char line[256];
    Config *config;

    file = f(open(path, "r"));
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
    memset(config, 0, sizeof(Config)); // Initialize all fields to NULL
}