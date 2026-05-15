#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "rest_api.h"


static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    // Unused callback suppression in write_callback statement before the fn is used.
    /** static size_t __attribute__((unused)) write_callback(void *contents, size_t size, size_t nmemb, void *userp) { */
    // Handle the response data here
    printf("Debug: write_callback called\n");
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

    snprintf(json, sizeof(json),
        "{ \"personalizations\": [ { \"to\": [ { \"email\": \"%s\" } ] } ], "
        "\"from\": { \"email\": \"%s\" }, "
        "\"subject\": \"%s\", "
        "\"content\": [ { \"type\": \"text/plain\", \"value\": \"%s\" } ] }",
        email->to, from, email->subject, email->body);

    snprintf(auth, sizeof(auth), "Authorization: Bearer %s", api_key);

    curl = curl_easy_init();
    
    if (curl == NULL) {
        printf("Error: could not initialize curl\n");
        return 0;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, auth);

    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.sendgrid.com/v3/mail/send");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        printf("Error: curl failed - %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return 0;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 1;
}

Transport rest_api_transport = {
    .name = "rest_api",
    .send = rest_api_send,
    .validate = NULL // No validation needed for REST API
};