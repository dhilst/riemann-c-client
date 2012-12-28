#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "riemann/event.h"
#include "riemann/query.h"
#include "riemann/message.h"
#include "riemann/client.h"

#define STATIC_ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char **argv)
{
        riemann_message_t msg = RIEMANN_MSG_INIT;
        riemann_message_t *resp; 
        riemann_query_t qry = RIEMANN_QUERY_INIT;
        riemann_client_t cli = RIEMANN_CLIENT_INIT;
        int i;

        if (argc != 3) {
                fprintf(stderr, "%s <IP> <PORT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        riemann_query_set_string(&qry, "true");
        riemann_message_set_query(&msg, &qry);

        riemann_client_connect(&cli, TCP, argv[1], atoi(argv[2]));
        riemann_client_send_message(&cli, &msg, 0, NULL);
        resp = riemann_client_recv_message(&cli, 0, NULL);

        if (!resp->ok) {
                fprintf(stderr, "Message error %s\n", resp->error);
                exit(EXIT_FAILURE);
        } else {
                puts("Sucess");
        }

        for (i = 0; i < resp->n_events; i++) 
                puts(resp->events[i]->service);

        riemann_message_free(resp); /* responses should be freed */
        riemann_client_free(&cli);        
        return 0;
}
