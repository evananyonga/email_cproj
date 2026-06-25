#include <stdio.h>
#include <string.h>
#include "test_framework.h"
#include "cli.h"

void test_cli_no_arguments(void) {
    int argc = 1;
    char *argv[] = {"./email"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args == NULL, "no arguments returns NULL");
}

void test_cli_valid_to_flag(void) {
    int argc = 3;
    char *argv[] = {"./email", "--to", "recipient@example.com"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --to flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->to, "recipient@example.com") == 0, "--to flag sets correct value");
    free_args(args);
}

void test_cli_valid_backend(void) {
    int argc = 3;
    char *argv[] = {"./email", "--backend", "smtp"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --backend flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->backend, "smtp") == 0, "--backend flag sets correct value");
    free_args(args);
}

void test_cli_invalid_argument(void) {
    int argc = 2;
    char *argv[] = {"./email", "--tikiroho"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args == NULL, "invalid argument returns NULL");
}

void test_cli_missing_value(void) {
    int argc = 2;
    char *argv[] = {"./email", "--to"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args == NULL, "missing value for --to parameter returns NULL");
}

int main() {
    TEST_RUN(test_cli_no_arguments);
    TEST_RUN(test_cli_valid_to_flag);
    TEST_RUN(test_cli_valid_backend);
    TEST_RUN(test_cli_invalid_argument);
    TEST_RUN(test_cli_missing_value);
    TEST_SUMMARY();
    return 0;
}