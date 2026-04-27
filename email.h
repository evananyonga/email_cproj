#ifndef EMAIL_H
#define EMAIL_H

typedef struct {
    char* from;
    char* to;
    char* subject;
    char* body;
} Email;

int validate_email(Email *email);
void print_email(Email *email);

#endif // EMAIL_H