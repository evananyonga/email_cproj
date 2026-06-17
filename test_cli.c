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

// void test_cli_help_flag() {
//     int argc = 2;
//     char *argv[] = {"./email", "--help"};
//     Args *args = parse_args(argc, argv);
//     TEST_ASSERT(args != NULL, "--help flag returns valid Args");
// }

// void test_cli_version_flag() {
//     int argc = 2;
//     char *argv[] = {"./email", "--version"};
//     Args *args = parse_args(argc, argv);
//     TEST_ASSERT(args != NULL, "--version flag returns valid Args");
// }

int main() {
    TEST_RUN(test_cli_no_arguments);
    TEST_RUN(test_cli_valid_to_flag);
    // TEST_RUN(test_cli_help_flag);
    // TEST_RUN(test_cli_version_flag);
    TEST_SUMMARY();
    return 0;
}