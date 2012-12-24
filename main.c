#include <stdio.h>
#include <stdlib.h>
#include "riemann_client.h"

static char *hosts[] = {
        "host-0",
        "host-1",
        "host-2",
        "host-3",
        "host-4",
        "host-5",
        "host-6",
        "host-7",
        "host-8",
        "host-9",
};


int main(void)
{
        riemann_events_t events;
        riemann_event_t *evtp;
        int error;
        int i;
        riemann_events_init(&events, 10); /* alloc space and initialize N events */
        
        FOR_EACH_EVENT(events, i, evtp) {
                riemann_event_set_host(evtp, hosts[i]);
                riemann_event_set_service(evtp, "cpu-idle");
                riemann_event_set_state(evtp, "ok");
                riemann_event_set_metric_f(evtp, 100l);
        }

        error = riemann_events_send_stdout(&events);
        if (error) {
                fprintf(stderr, "Can't send events to stdout");
                exit(EXIT_FAILURE);
        }
        return 0;
}
