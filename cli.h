#ifndef CLI_H
#define CLI_H

typedef struct {
    char *to;
    char *from;
    char *subject;
    char *body;
    char *backend;
    char *port;
    char *config_path;
} Args;

Args *parse_args(int argc, char *argv[]);

void free_args(Args *a);
void print_usage(void);

#endif