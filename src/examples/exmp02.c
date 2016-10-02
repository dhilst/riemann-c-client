/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <riemann/event.h>
#include <riemann/query.h>
#include <riemann/message.h>
#include <riemann/client.h>

#define STATIC_ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

static char buffer[BUFSIZ];

int main(int argc, char **argv)
{
        riemann_message_t msg = RIEMANN_MSG_INIT;
        riemann_message_t *resp; 
        riemann_query_t qry = RIEMANN_QUERY_INIT;
        riemann_client_t cli;
        int i;
        int error;

        if (argc != 4) {
                fprintf(stderr, "%s <IP> <PORT> <FMT>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        riemann_query_set_string(&qry, "true");
        riemann_message_set_query(&msg, &qry);

        riemann_client_init(&cli);
        riemann_client_connect(&cli, RIEMANN_TCP, argv[1], atoi(argv[2]));
        riemann_client_send_message(&cli, &msg, 0, NULL);
        resp = riemann_client_recv_message(&cli, 0, NULL);

        if (!resp->ok) {
                fprintf(stderr, "Message error %s\n", resp->error);
                exit(EXIT_FAILURE);
        } else {
                puts("Sucess");
        }

        for (i = 0; i < resp->n_events; i++) {
                error = riemann_event_strfevent(buffer, BUFSIZ, argv[3], resp->events[i]);
                if (error) {
                        fprintf(stderr, "riemann_event_strfevent() error\n");
                        exit(EXIT_FAILURE);
                }
                puts(buffer);
        }

        riemann_message_free(resp); /* responses should be freed */
        riemann_client_free(&cli);        
        return 0;
}
