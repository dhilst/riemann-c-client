#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

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

int main(int argc, char **argv)
{
        riemann_udp_client_t cli;
        riemann_events_t events;
        riemann_event_t *evtp;
        const char *tags[] = { "cpu", "performance", "load", };
        int n_tags;
        int error;
        int i;

        if (argc != 3) {
                fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        error = riemann_events_init(&events, 10); /* alloc space and initialize N events */
        if (error) {
                fprintf(stderr, "Can't allocate events: %d\n", error);
                exit(EXIT_FAILURE);
        }
        
        n_tags = sizeof(tags) / sizeof(tags[0]); /* number of tags */
        FOR_EACH_EVENT(events, i, evtp) {        /* evtp points to each event (events->events[i]) inside FOR loop */
                riemann_event_set_host(evtp, hosts[i]); /* i goes from 0 to events->n_events */
                riemann_event_set_service(evtp, "cpu-idle"); /* (char *) attributes are strduped */
                riemann_event_set_state(evtp, "ok");
                riemann_event_set_metric_f(evtp, 100l);
                riemann_event_set_tags(evtp, tags, n_tags); /* tags are strdupded too */
                riemann_event_set_description(evtp, "Percent cpu idle time");
        }

        cli = RIEMANN_UDP_CLIENT_INIT;
        error = riemann_udp_client_create(&cli, argv[1], atoi(argv[2]));
        if (error) {
                fprintf(stderr, "Can't create UDP client\n");
                exit(EXIT_FAILURE);
        }

        riemann_udp_client_free(&cli);
        riemann_events_free(&events); /* free event attributes, and events */
        return 0;
}
