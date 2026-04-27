#include <stdio.h>
#include "email.h"

int main() {
    Email email;

    email.from = "alice@example.com";
    email.to = "bob@example.com";
    email.subject = "Hello";
    email.body = "Hi Bob, How are you?";

    if (validate_email(&email)) {
        printf("Email is valid.  Printing...\n");
        print_email(&email);
    } else {
        printf("Email is invalid.  Aborting.\n");
    }

    return 0;
}