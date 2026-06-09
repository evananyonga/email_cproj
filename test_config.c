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