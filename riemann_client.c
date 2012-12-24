#include "riemann_client.h"

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

static  riemann_msg_send_stdout(Msg *msg)
{
        uint8_t *buf;
        int len;

        len = msg__get_packed_size(msg);
        if (len <= 0)
                return -1;

        buf = xmalloc(len);

        len = msg__pack(msg, buf);
        
        fwrite(buf, len, 1, stdout);
        if (ferror(stdout))
                return -2;
        return 0;
}

/* @TODO:
 * - Implement human readable errors
 */
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
                                free(events->events[i]);
                                events->events[i] = NULL;
                        }
                        free(events->events);
                        return -2;
                }
                riemann_event_init(events->events[i]);
        }
        return 0;
}

int riemann_events_free(riemann_events_t *evts)
{
        int i;
       
        for (i = 0; i < evts->n_events; i++) {
                xfree(evts->events[i]);
        }
        xfree(evts->events);
        evts->n_events = 0;
}

int riemann_events_send_stdout(riemann_events_t *evts)
{
        Msg msg = MSG__INIT;
        msg.n_events = evts->n_events;
        msg.events = evts->events;

        return riemann_msg_send_stdout(&msg);
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
