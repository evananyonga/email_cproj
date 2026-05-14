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