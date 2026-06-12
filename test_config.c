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
    fprintf(file, "default_backend: smtp\n");
    fprintf(file, "smtp_host: smtp.gmail.com\n");
    fprintf(file, "smtp_port: 587\n");
    fprintf(file, "smtp_user: user@example.com\n");
    fprintf(file, "smtp_password: password\n");
    fprintf(file, "smtp_from: from@example.com\n");
    fprintf(file, "smtp_to: to@example.com\n");
    fprintf(file, "rest_api_key: test_api_key\n");
    fprintf(file, "rest_provider_url: https://rest.example.com/api\n");
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

void test_config_fields(void) {
    create_test_config();

    Config *conf = load_config(TEST_CONFIG_PATH);
    TEST_ASSERT(conf != NULL, "valid config loads successfully");

    printf("DEBUG: default_backend=%s\n", conf->default_backend ? conf->default_backend : "NULL");
    printf("DEBUG: smtp_host=%s\n", conf->smtp_host ? conf->smtp_host : "NULL");
    printf("DEBUG: smtp_port=%s\n", conf->smtp_port ? conf->smtp_port : "NULL");
    printf("DEBUG: smtp_user=%s\n", conf->smtp_user ? conf->smtp_user : "NULL");
    printf("DEBUG: smtp_password=%s\n", conf->smtp_password ? conf->smtp_password : "NULL");
    printf("DEBUG: smtp_from=%s\n", conf->smtp_from ? conf->smtp_from : "NULL");
    printf("DEBUG: smtp_to=%s\n", conf->smtp_to ? conf->smtp_to : "NULL");
    printf("DEBUG: rest_api_key=%s\n", conf->rest_api_key ? conf->rest_api_key : "NULL");
    printf("DEBUG: rest_provider_url=%s\n", conf->rest_provider_url ? conf->rest_provider_url : "NULL");

    TEST_ASSERT(strcmp(conf->default_backend, "smtp") == 0, "default_backend should be smtp");
    TEST_ASSERT(strcmp(conf->smtp_host, "smtp.gmail.com") == 0, "smtp_host should be smtp.gmail.com");
    TEST_ASSERT(strcmp(conf->smtp_port, "587") == 0, "smtp_port should be 587");
    TEST_ASSERT(strcmp(conf->smtp_user, "user@example.com") == 0, "smtp_user should be user@example.com");
    TEST_ASSERT(strcmp(conf->smtp_password, "password") == 0, "smtp_password should be password");
    TEST_ASSERT(strcmp(conf->smtp_from, "from@example.com") == 0, "smtp_from should be from@example.com");
    TEST_ASSERT(strcmp(conf->smtp_to, "to@example.com") == 0, "smtp_to should be to@example.com");
    TEST_ASSERT(strcmp(conf->rest_api_key, "test_api_key") == 0, "rest_api_key should be test_api_key");
    TEST_ASSERT(strcmp(conf->rest_provider_url, "https://rest.example.com/api") == 0, "rest_provider_url should be https://rest.example.com/api");

    free_config(conf);

    cleanup_test_config();
}

void test_config_malformed_line(void) {
    create_test_config();
    Config *c = load_config(TEST_CONFIG_PATH);
    TEST_ASSERT(c != NULL, "config loads despite malformed line");
    free_config(c);
    cleanup_test_config();
}

int main() {
    TEST_RUN(test_config_missing_file);
    TEST_RUN(test_config_loads_successfully);
    TEST_RUN(test_config_fields);
    TEST_RUN(test_config_malformed_line);
    TEST_SUMMARY();

    return 0;
}