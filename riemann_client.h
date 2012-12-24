#include <string.h>
#include "proto.pb-c.h"
#include "common.h"

typedef Event riemann_event_t;

struct _riemann_events_s {
        riemann_event_t **events;
        int n_events;
};
typedef struct _riemann_events_s riemann_events_t;

/* Closing culry bracke is madatory here */
#define FOR_EACH_EVENT(events, i, evtp) \
        for(i = 0, evtp = events.events[i]; i < events.n_events; i++, evtp = events.events[i])



void riemann_events_init(riemann_events_t *events, size_t n_events);
int rimeann_events_send_stdout(riemann_events_t *evts);
void riemann_event_set_host(riemann_event_t *evtp, const char *host);
void riemann_event_set_service(riemann_event_t *evtp, const char *service);
void riemann_event_set_state(riemann_event_t *evtp, const char *state);
void riemann_event_set_metric_f(riemann_event_t *evtp, const float metric);
