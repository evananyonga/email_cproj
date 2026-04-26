#ifndef EMAIL_H
#define EMAIL_H

typedef struct {
    char* from;
    char* to;
    char* subject;
    char* body;
} Email;

#endif // EMAIL_H