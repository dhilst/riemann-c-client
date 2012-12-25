#ifndef RIEMANN_CLIENT_H
# define RIEMANN_CLIENT_H

#include <stdio.h>
#include "proto.pb-c.h"

typedef Event riemann_event_t;

struct riemann_events_s {
        riemann_event_t **events;
        int n_events;
};
typedef struct riemann_events_s riemann_events_t;

struct riemann_udp_client_s {
        int sock;
        struct addrinfo *srv_addrinfo;
};
typedef struct riemann_udp_client_s riemann_udp_client_t;


/* Closing culry bracke is madatory here */
#define FOR_EACH_EVENT(events, i, evtp) \
        for(i = 0, evtp = events.events[i]; i < events.n_events; i++, evtp = events.events[i])

uint8_t* riemann_events_pack(riemann_events_t *evts, size_t *len); // remover

int riemann_events_init(riemann_events_t *events, size_t n_events);
void riemann_event_set_host(riemann_event_t *evtp, const char *host);
void riemann_event_set_service(riemann_event_t *evtp, const char *service);
void riemann_event_set_state(riemann_event_t *evtp, const char *state);
void riemann_event_set_metric_f(riemann_event_t *evtp, const float metric);
int riemann_events_send_stream(riemann_events_t *evts, FILE *stream);
int riemann_events_send_udp(riemann_udp_client_t *cli, riemann_events_t *evts);

/* UDP */
#define RIEMANN_UDP_CLIENT_INIT \
        (riemann_udp_client_t) { .sock =  -1,   \
                        .srv_addrinfo  = NULL }

int riemann_udp_client_create(riemann_udp_client_t *cli, const char* hostname, uint16_t port);
void riemann_udp_client_free(riemann_udp_client_t *cli);



#endif
