#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_framework.h"
#include "config.h"

#define TEST_CONFIG_PATH "/tmp/test_email_app.config"

static void create_test_config(void) {
    FILE *file = fopen(TEST_CONFIG_PATH, "w");
    if (file == NULL) return;

    fprintf(file, "# Test configuration for email app\n");
    fprintf(file, "default_backend: sendmail\n");
    fprintf(file, "smtp_host: smtp.gmail.com\n");
    fprintf(file, "smtp_port: 587\n");
    fprintf(file, "smtp_user: user@example.com\n");
    fprintf(file, "smtp_pass: password\n");
    fprintf(file, "smtp_from: from@example.com\n");
    fprintf(file, "smtp_to: to@example.com\n");
    fprintf(file, "rest_provider: sendmail\n");
    fprintf(file, "rest_api_key: test_api_key\n");
    fprintf(file, "rest_api_url: https://rest.example.com/api\n");
    fprintf(file, "malformed value without equals\n");

    fclose(file);
}

static void cleanup_test_config(void) {
    remove(TEST_CONFIG_PATH);
}

void test_config_missing_file(void) {
    create_test_config();
    cleanup_test_config();

    Config *config = load_config(TEST_CONFIG_PATH);
    TEST_ASSERT(config == NULL, "Expected NULL for missing config file");
    free_config(config);
}

void test_config_loads_successfully(void) {
    create_test_config();

    Config *config = load_config(TEST_CONFIG_PATH);
    TEST_ASSERT(config != NULL, "valid config loads successfully");
    free_config(config);

    cleanup_test_config();
}

void test_config_default_exists(void) {
    create_test_config();

    Config *conf = load_config(TEST_CONFIG_PATH);
    TEST_ASSERT(conf != NULL, "valid config loads successfully");
    TEST_ASSERT(conf->default_backend != NULL, "default_backend should not be NULL");
    free_config(conf);

    cleanup_test_config();
}

int main() {
    TEST_RUN(test_config_missing_file);
    TEST_RUN(test_config_loads_successfully);
    TEST_RUN(test_config_default_exists);
    TEST_SUMMARY();

    return 0;
}