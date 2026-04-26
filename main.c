#include <stdio.h>
#include "email.h"

int main() {
    Email email;

    email.from = "alice@example.com";
    email.to = "bob@example.com";
    email.subject = "Hello";
    email.body = "Hi Bob, How are you?";

    printf("From: %s\n", email.from);
    printf("To: %s\n", email.to);
    printf("Subject: %s\n", email.subject);
    printf("Body: %s\n", email.body);

    return 0;
}