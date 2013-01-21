#ifndef RIEMANN_EVENT_H
# define RIEMANN_EVENT_H

#include <string.h>

#include <riemann/attribute.h>
#include <riemann/proto.pb-c.h>

typedef Event riemann_event_t;
#define RIEMANN_EVENT_INIT EVENT__INIT

void riemann_event_init(riemann_event_t *evt);
riemann_event_t *riemann_event_alloc_event(void);
riemann_event_t **riemann_event_alloc_events(size_t n_events);
void riemann_event_free(riemann_event_t *e);
void riemann_events_free(riemann_event_t **evts, size_t n_events);
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
int riemann_event_set_attributes(riemann_event_t *evtp, const riemann_attribute_pairs_t *apairsp, size_t n_attrs);
#endif 
