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

void test_cli_valid_from(void) {
    int argc = 5;
    char *argv[] = {"./email", "--from", "sender@example.com", "--to", "recipient@example.com"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --from flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->from, "sender@example.com") == 0, "--from flag sets correct value");
    free_args(args);
}

void test_cli_valid_subject(void) {
    int argc = 5;
    char *argv[] = {"./email", "--subject", "Test Subject", "--to", "recipient@example.com"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --subject flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->subject, "Test Subject") == 0, "--subject flag sets correct value");
    free_args(args);
}

void test_cli_valid_port(void) {
    int argc = 5;
    char *argv[] = {"./email", "--port", "587", "--to", "recipient@example.com"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --port flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->port, "587") == 0, "--port flag sets correct value");
    free_args(args);
}

void test_cli_valid_backend(void) {
    int argc = 5;
    char *argv[] = {"./email", "--to", "recipient@example.com", "--backend", "smtp"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --backend flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->backend, "smtp") == 0, "--backend flag sets correct value");
    free_args(args);
}

void test_cli_valid_config(void) {
    int argc = 5;
    char *argv[] = {"./email", "--to", "recipient@example.com", "--config", "/path/to/config"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --config flag returns valid Args-non-NULL");
    TEST_ASSERT(strcmp(args->config_path, "/path/to/config") == 0, "--config flag sets correct value");
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

void test_cli_required_arguments(void) {
    int argc = 3;
    char *argv[] = {"./email", "--body", "Hello there!"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args == NULL, "missing value for --to parameter returns NULL");
}

void test_cli_help_flag(void) {
    int argc = 2;
    char *argv[] = {"./email", "--help"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args != NULL, "valid --help flag returns valid Args-non-NULL");
    TEST_ASSERT(args->help == 1, "--help flag sets correct value");
    free_args(args);
}

int main() {
    TEST_RUN(test_cli_no_arguments);
    TEST_RUN(test_cli_valid_to_flag);
    TEST_RUN(test_cli_valid_from);
    TEST_RUN(test_cli_valid_subject);
    TEST_RUN(test_cli_valid_port);
    TEST_RUN(test_cli_valid_backend);
    TEST_RUN(test_cli_valid_config);
    TEST_RUN(test_cli_invalid_argument);
    TEST_RUN(test_cli_missing_value);
    TEST_RUN(test_cli_required_arguments);
    TEST_RUN(test_cli_help_flag);
    TEST_SUMMARY();
    return 0;
}