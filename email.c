#include <stdio.h>
#include <string.h>
#include "email.h"

int validate_email(Email *email) {
    if (email->from == NULL || email->from == 0) {
        printf("Error: From field is empty\n");
        return 0; // Invalid email
    }
    if (email->to == NULL || strlen(email->to) == 0) {
        printf("Error: To field is empty\n");
        return 0; // From field cannot be empty
    }
    if (email->subject == NULL || strlen(email->subject) == 0) {
        printf("Error: Subject field is empty\n");
        return 0; // Subject field cannot be empty
    }
    if (email->body == NULL || strlen(email->body) == 0) {
        printf("Error: Body field is empty\n");
        return 0; // Body field cannot be empty
    }
    return 1; // Valid email
}