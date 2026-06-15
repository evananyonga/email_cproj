#include <stdio.h>
#include "test_framework.h"
#include "cli.h"

void test_cli_no_arguments() {
    int argc = 1;
    char *argv[] = {"./email"};
    Args *args = parse_args(argc, argv);
    TEST_ASSERT(args == NULL, "no arguments returns NULL");
}

int main() {
    TEST_RUN(test_cli_no_arguments);
    TEST_SUMMARY();
    return 0;
}