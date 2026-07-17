#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_framework.h"
#include "transport.h"

/** 
 * test_transport_is_set
 * test_transport_sends_via_smtp
 * test_transport_sends_via_sendmail
 * test_transport_sends_via_rest_api
 * test_security_layer_is_established
 * test_transport_fails_with_network_error
 * test_transport_fails_with_unreachable_smtp_host
 * test_transport_fails_with_timeout
 */

void test_transport_is_set(void) {
    Transport *transport = get_transport("smtp");
    TEST_ASSERT(transport != NULL, "SMTP transport should be available");
}

int main() {
    TEST_RUN(test_transport_is_set);
    return tests_failed > 0 ? 1 : 0;    
}