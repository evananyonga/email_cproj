#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "email.h"

typedef struct {
    const char* name;
    int (*send)(const Email *email);
    int (*validate)(void);
} Transport;

Transport *get_transport(const char *name);

#endif // TRANSPORT_H