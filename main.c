#include <stdio.h>
#include "email.h"
#include "transport.h"

int main() {
    Email email;

    email.from = "alice@example.com";
    email.to = "bob@example.com";
    email.subject = "Hello";
    email.body = "Hi Bob, How are you?";

    if (!validate_email(&email)) {
        printf("Email is invalid.  Aborting...\n");
        return 1;
    }

    Transport *transport = get_transport("sendmail");
    if (transport == NULL) {
        printf("Error: No transport found for sendmail\n");
        return 1;
    }

    transport->send(&email);

    return 0;
}