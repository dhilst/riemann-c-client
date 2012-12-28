#include <endian.h>
#include <stdlib.h>
#include <string.h>

#include "riemann_client.h"
#include "common.h"
#include "proto.pb-c.h"

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

static void riemann_event_free(riemann_event_t *e)
{
        if (e->state)
                free(e->state);
        e->state = NULL;

        if (e->service)
                free(e->service);
        e->service = NULL;

        if (e->host)
                free(e->host);
        e->host = NULL;

        if (e->description)
                free(e->description);
        e->description = NULL;

        if (e->n_tags > 0) {
                int i;
                for (i = 0; i < e->n_tags; i++) {
                        free(e->tags[i]);
                        e->tags[i] = NULL;
                }
                free(e->tags);
                e->tags = NULL;
                e->n_tags = 0;
        }
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
                riemann_event_free(evts->events[i]);
                xfree(evts->events[i]);
        }
        xfree(evts->events);
        evts->n_events = 0;
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
