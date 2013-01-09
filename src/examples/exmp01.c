#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <riemann/event.h>
#include <riemann/message.h>
#include <riemann/client.h>

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
        riemann_message_t *resp = NULL;
        size_t n_events = STATIC_ARRAY_SIZE(cpus);
        riemann_event_t *events[n_events]; /* using stack space */

        int i;
        int error;
        riemann_client_t cli;

        if (argc != 3) {
                fprintf(stderr, "%s <IP> <PORT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        for (i = 0; i < n_events; i++) {
                events[i] = alloca(sizeof (riemann_event_t));
                riemann_event_init(events[i]);
                riemann_event_set_host(events[i], "gentoo-x86");
                riemann_event_set_service(events[i], cpus[i]);
                riemann_event_set_metric_f(events[i], 100); /* 100% idle */
                riemann_event_set_state(events[i], "ok");
                riemann_event_set_tags(events[i], tags, STATIC_ARRAY_SIZE(tags));
        }

        riemann_message_set_events(&msg, events, n_events);
        
        error = riemann_client_init(&cli);
        if (error) {
                fprintf(stderr, "Can't initialize client: strerror(%s)\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        error = riemann_client_connect(&cli, TCP, argv[1], atoi(argv[2])); /* functions that returns ints returns 0 on success */
        if (error) {
                fprintf(stderr, "Can't connectd: strerror(%s) gai_strerrror(%s)\n", strerror(errno), gai_strerror(error));
                exit(EXIT_FAILURE);
        }

        error = riemann_client_send_message(&cli, &msg, 0, NULL);
        if (error) {
                fprintf(stderr, "Can't send message: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }

        resp = riemann_client_recv_message(&cli, 0, NULL); /* functions that returns pointers rertuns NULL on failure */
        assert(resp);

        if (!resp->ok) {
                fprintf(stderr, "Message error %s\n", resp->error);
                exit(EXIT_FAILURE);
        } else {
                puts("Sucess");
        }

        riemann_message_free(resp); /* responses should be freed */
        riemann_client_free(&cli);

        return 0;
}

        
        


