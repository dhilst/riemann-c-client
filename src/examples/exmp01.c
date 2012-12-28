#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "riemann/event.h"
#include "riemann/message.h"
#include "riemann/client.h"

static char *cpus[] = {
        "cpu-0",
        "cpu-1",
        "cpu-2",
        "cpu-3",
};

static const char *tags[] = {
        "cpu",
        "idle",
        "performance",
};

#define STATIC_ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char **argv)
{
        riemann_message_t msg = RIEMANN_MSG_INIT;
        riemann_message_t *resp;
        riemann_event_t **events;
        size_t n_events = STATIC_ARRAY_SIZE(cpus);
        int i;
        riemann_client_t cli = RIEMANN_CLIENT_INIT;

        if (argc != 3) {
                fprintf(stderr, "%s <IP> <PORT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        events = riemann_event_alloc_events(n_events);
        assert(events);
        for (i = 0; i < n_events; i++) {
                events[i] = riemann_event_alloc_event();
                assert(events[i]);
                riemann_event_init(events[i]);
                riemann_event_set_host(events[i], "gentoo-x86");
                riemann_event_set_service(events[i], cpus[i]);
                riemann_event_set_metric_f(events[i], 100); /* 100% idle */
                riemann_event_set_state(events[i], "ok");
                riemann_event_set_tags(events[i], tags, STATIC_ARRAY_SIZE(tags));
        }

        riemann_message_set_events(&msg, events, n_events);
        
        riemann_client_connect(&cli, TCP, argv[1], atoi(argv[2]));
        riemann_client_send_message(&cli, &msg, 0, NULL);
        resp = riemann_client_recv_message(&cli, 0, NULL);

        if (!resp->ok) {
                fprintf(stderr, "Message error %s\n", resp->error);
                exit(EXIT_FAILURE);
        } else {
                puts("Sucess");
        }

        riemann_message_free(resp); /* responses should be freed */
        riemann_events_free(events, n_events);
        riemann_client_free(&cli);

        return 0;
}

        
        


