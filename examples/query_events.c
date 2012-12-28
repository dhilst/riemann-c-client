#include <stdio.h>
#include <stdlib.h>

#include "riemann_client.h"
#include "proto.pb-c.h"
#include "common.h"
#include "query.h"

int main(int argc, char **argv)
{
        int error;
        riemann_tcp_client_t cli = RIEMANN_TCP_CLIENT_INIT;
        riemann_events_t *evts;

        if (argc != 3) {
                fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        error = riemann_tcp_client_connect(&cli, argv[1], atoi(argv[2]));
        if (error) {
                fprintf(stderr, "Can't create tcp client\n");
                exit(EXIT_FAILURE);
        }

        evts = riemann_query_tcp_send(&cli, "true");

        int i;
        for (i = 0; i < evts->n_events; i++) {
                printf("%s\n", evts->events[i]->service);
        }
        return 0;
}
