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


int riemann_events_init(riemann_events_t *events, size_t n_events);
void riemann_events_free(riemann_events_t *evts);
int riemann_events_send_stream(riemann_events_t *evts, FILE *stream);
int riemann_events_send_udp(riemann_udp_client_t *cli, riemann_events_t *evts);;
void riemann_event_set_host(riemann_event_t *evtp, const char *host);
void riemann_event_set_service(riemann_event_t *evtp, const char *service);
void riemann_event_set_state(riemann_event_t *evtp, const char *state);
void riemann_event_set_metric_f(riemann_event_t *evtp, const float metric);
void riemann_event_set_time(riemann_event_t *evtp, const int64_t time);
void riemann_event_set_description(riemann_event_t *evtp, const char *desc);
int riemann_event_set_tags(riemann_event_t *evtp, const char **tags, size_t n_tags);
void  riemann_event_set_ttl(riemann_event_t *evtp, float ttl);
void riemann_event_set_metric_sint64(riemann_event_t *evtp, int64_t metric);
void riemann_event_set_metric_d(riemann_event_t *evtp, double metric);


/* UDP */
#define RIEMANN_UDP_CLIENT_INIT \
        (riemann_udp_client_t) { .sock =  -1,   \
                        .srv_addrinfo  = NULL }

int riemann_udp_client_create(riemann_udp_client_t *cli, const char* hostname, uint16_t port);
void riemann_udp_client_free(riemann_udp_client_t *cli);



#endif
