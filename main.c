#include <stdio.h>
#include "email.h"
#include "transport.h"

int main() {
    Email email;

    email.from = getenv("SMTP_FROM");
    email.to = getenv("SMTP_TO");
    email.subject = "Hello from your the other side";
    email.body = "Be Afraid, be very afraid.  I am coming for you.";

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