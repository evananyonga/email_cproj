#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "email.h"
#include "config.h"

typedef struct {
    const char* name;
    int (*send)(const Email *email, const Config *config);
    int (*validate)(void);
} Transport;

Transport *get_transport(const char *name);

#endif // TRANSPORT_H