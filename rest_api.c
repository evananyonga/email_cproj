#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "rest_api.h"


static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    // Unused callback suppression in write_callback statement before the fn is used.
    /** static size_t __attribute__((unused)) write_callback(void *contents, size_t size, size_t nmemb, void *userp) { */
    // Handle the response data here
    size_t total = size * nmemb;
    (void)userp; // Unused parameter
    printf("SendGrid response: %.*s\n", (int)total, (char *)contents);

    return total;
}

static int rest_api_send(const Email *email) {
    CURL *curl;
    CURLcode res;

    char json[1024];
    char auth[256];
    
    const char *api_key = getenv("SENDGRID_API_KEY");
    const char *from = getenv("SENDGRID_FROM");

    if (api_key == NULL || from == NULL) {
        printf("Error: SENDGRID_API_KEY or SENDGRID_FROM environment variables not set\n");
        return 0;
    }
}