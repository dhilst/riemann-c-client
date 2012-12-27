#include <stdlib.h>
#include <string.h>

#include "riemann_client.h"
#include "common.h"
#include "udp.h"
#include "proto.pb-c.h"

#define RIEMANN_EVENT_INIT EVENT__INIT

static void riemann_event_init(riemann_event_t *evt)
{
        event__init((Event *) evt);
}

static riemann_event_t *riemann_event_alloc_event(void)
{
        return (malloc(sizeof (riemann_event_t)));
}

static riemann_event_t **rieman_event_alloc_events(size_t n_events)
{
        return (malloc(sizeof (riemann_event_t *) * n_events));
}

uint8_t* riemann_events_pack(riemann_events_t *evts, size_t *len)
{
        Msg msg = MSG__INIT;
        uint8_t *buf;

        msg.events = evts->events;
        msg.n_events = evts->n_events;
        *len = msg__get_packed_size(&msg);
        buf = malloc(*len);
        if (!buf) {
                fprintf(stderr, "riemann_client.c riemann_events_pack(%d): malloc() fails\n", __LINE__);
                return NULL;
        }

        msg__pack(&msg, buf);
        return buf;
}
                                                
int riemann_events_init(riemann_events_t *events, size_t n_events)
{
        int i;

        events->events = rieman_event_alloc_events(n_events);
        if (!events->events)
                return -1;
        events->n_events = n_events;

        for (i = 0; i < n_events; i++) {
                events->events[i] = riemann_event_alloc_event();
                if (!events->events[i]) { 
                        int j;
                        for (j = 0; j < i; j++) {
                                xfree(events->events[j]);
                                events->events[j] = NULL;
                        }
                        xfree(events->events);
                        return -2;
                }
                riemann_event_init(events->events[i]);
        }
        return 0;
}

void riemann_events_free(riemann_events_t *evts)
{
        int i;
       
        for (i = 0; i < evts->n_events; i++) {
                xfree(evts->events[i]);
        }
        xfree(evts->events);
        evts->n_events = 0;
}

int riemann_events_send_stream(riemann_events_t *evts, FILE *stream)
{
        uint8_t *buf;
        size_t len;

        buf = riemann_events_pack(evts, &len);
        if (!buf) {
                fprintf(stderr, "riemann_client.c riemann_events_send_stream(%d): riemann_events_pack() fails\n", __LINE__);
                return -1;
        }

        fwrite(buf, len, 1, stream);
        if (ferror(stream)) {
                fprintf(stderr, "riemann_client.c riemann_events_send_stream(%d): Error while sending data to stream\n", __LINE__);
                return -2;
        }
        return 0;
}

int riemann_events_send_udp(riemann_udp_client_t *cli, riemann_events_t *evts)
{
        uint8_t *buf;
        size_t len;
        int error;
        
        buf = riemann_events_pack(evts, &len);
        if (!buf) {
                fprintf(stderr, "riemann_client.c riemann_events_send_udp(%d): riemann_events_pack() fails\n", __LINE__);
                return -1;
        }

        error = riemann_udp_client_send(cli, buf, len, 0);
        if (error) {
                fprintf(stderr, "riemann_client.c riemann_events_send_udp(%d): Error while send data to server\n", __LINE__);
                return -2;
        }
        
        return 0;                
}

void riemann_event_set_host(riemann_event_t *evtp, const char *host)
{
        evtp->host = strdup(host);
}

void riemann_event_set_service(riemann_event_t *evtp, const char *service)
{
        evtp->service = strdup(service);
}

void riemann_event_set_state(riemann_event_t *evtp, const char *state)
{
        evtp->state = strdup(state);
}

void riemann_event_set_metric_f(riemann_event_t *evtp, const float metric)
{
        evtp->metric_f = metric;
        evtp->has_metric_f = 1;
}

void riemann_event_set_time(riemann_event_t *evtp, const int64_t time)
{
        evtp->time = time;
        evtp->has_time = 1;
}

void riemann_event_set_description(riemann_event_t *evtp, const char *desc)
{
        evtp->description = strdup(desc);
}

int riemann_event_set_tags(riemann_event_t *evtp, const char **tags, size_t n_tags)
{
        int i;

        evtp->tags = malloc(sizeof (char *) * n_tags);
        if (!evtp->tags)
                return -1;

        for (i = 0; i < n_tags; i++) 
                evtp->tags[i] = strdup(tags[i]);
        evtp->n_tags = n_tags;
        return 0;
}

void  riemann_event_set_ttl(riemann_event_t *evtp, float ttl)
{
        evtp->ttl = ttl;
        evtp->has_ttl = 1;
}

void riemann_event_set_metric_sint64(riemann_event_t *evtp, int64_t metric)
{
        evtp->metric_sint64 = metric;
        evtp->has_metric_sint64 = 1;
}

void riemann_event_set_metric_d(riemann_event_t *evtp, double metric)
{
        evtp->metric_d = metric;
        evtp->has_metric_d = 1;
}


