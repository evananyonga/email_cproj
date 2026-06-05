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

void test_to_is_valid() {
    Email email;
    email.from = "email@email.com";
    email.to = "recipient@email.com";
    email.subject = "Test Hello";
    email.body = "Test Body";
    TEST_ASSERT(validate_email(&email) == 1, "Valid email passes validation");

    email.to = "";
    TEST_ASSERT(validate_email(&email) == 0, "Empty to email fails validation");

    email.to = NULL;
    TEST_ASSERT(validate_email(&email) == 0, "NULL to email fails validation");
}

void test_email_has_subject() {
    Email email;
    email.from = "email@email.com";
    email.to = "recipient@email.com";
    email.subject = "Test Hello";
    email.body = "Test Body";
    TEST_ASSERT(validate_email(&email) == 1, "Valid email passes validation");

    email.subject = "";
    TEST_ASSERT(validate_email(&email) == 0, "Empty subject email fails validation");

    email.subject = NULL;
    TEST_ASSERT(validate_email(&email) == 0, "NULL subject email fails validation");
}

void test_email_has_body() {
    Email email;
    email.from = "email@email.com";
    email.to = "recipient@email.com";
    email.subject = "Test Hello";
    email.body = "Test Body";
    TEST_ASSERT(validate_email(&email) == 1, "Valid email passes validation");

    email.body = "";
    TEST_ASSERT(validate_email(&email) == 0, "Empty body email fails validation");

    email.body = NULL;
    TEST_ASSERT(validate_email(&email) == 0, "NULL body email fails validation");
}

int main() {
    TEST_RUN(test_from_is_valid);
    TEST_RUN(test_to_is_valid);
    TEST_RUN(test_email_has_subject);
    TEST_RUN(test_email_has_body);
    TEST_SUMMARY();
    return tests_failed > 0 ? 1 : 0;
}