#include "test_framework.h"
#include "email.h"

void test_from_is_valid() {
    Email email;
    email.from = "email@email.com";
    email.to = "recipient@email.com";
    email.subject = "Test Hello";
    email.body = "Test Body";
    TEST_ASSERT(validate_email(&email) == 1, "Valid email passes validation");

    email.from = "";
    TEST_ASSERT(validate_email(&email) == 0, "Empty from email fails validation");

    email.from = NULL;
    TEST_ASSERT(validate_email(&email) == 0, "NULL from email fails validation");
}

int main() {
    TEST_RUN(test_from_is_valid);
    TEST_SUMMARY();
    return tests_failed > 0 ? 1 : 0;
}