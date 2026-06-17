#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

void print_usage(void) {
    printf("Usage: email [options]\n");
    printf("  --to        recipient email address\n");
    printf("  --from      sender email address\n");
    printf("  --subject   email subject\n");
    printf("  --body      email body\n");
    printf("  --backend   sendmail, smtp, or rest_api\n");
    printf("  --port      smtp port (default 465)\n");
    printf("  --config    path to config file\n");
    printf("  --help      show this help\n");
}

Args *parse_args(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: No arguments provided.\n");
        print_usage();
        return NULL;
    }

    Args *args = malloc(sizeof(Args));
    if (args == NULL) return NULL;

    memset(args, 0, sizeof(Args));

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--to") == 0 && i + 1 < argc) {
            args->to = strdup(argv[++i]);
        }
    }

    return args;
}

void free_args(Args *a) {
    if (a == NULL) return;
    free(a);
}