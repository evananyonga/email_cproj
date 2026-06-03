#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define TEST_ASSERT(condition, message) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("PASS: %s\n", message); \
    } else { \
        tests_failed++; \
        printf("FAIL: %s, at %s:%d\n", message, __FILE__, __LINE__); \
    } \
} while (0)

#define TEST_RUN(test) do { \
    printf("\nRunning tests for %s...\n", #test); \
    test(); \
} while (0)

#define TEST_SUMMARY() do { \
    printf("\n====================\n"); \
    printf("Tests run: %d\n", tests_run); \
    printf("Tests passed: %d\n", tests_passed); \
    printf("Tests failed: %d\n", tests_failed); \
    printf("====================\n"); \
} while (0)

#endif // TEST_FRAMEWORK_H