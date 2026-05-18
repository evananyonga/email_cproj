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
}