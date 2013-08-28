#include <stdlib.h>

#if RIEMANN_HAVE_INTTYPES_H
# include <inttypes.h>
#endif

#include <time.h>
#include <string.h>

#include <riemann/_config.h>
#include <riemann/attribute.h>
#include <riemann/event.h>


void riemann_event_init(riemann_event_t *evt)
{
        event__init((Event *) evt);
}

riemann_event_t *riemann_event_alloc_event(void)
{
        return (malloc(sizeof (riemann_event_t)));
}

riemann_event_t **riemann_event_alloc_events(size_t n_events)
{
        return (malloc(sizeof (riemann_event_t *) * n_events));
}

void riemann_event_free(riemann_event_t *e)
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

        if (e->n_attributes > 0) {
                int i = 0;
                for (i = 0; i < e->n_attributes; i++) 
                        free(e->attributes[i]);
                e->attributes = NULL;
                e->n_attributes = 0;
        }
}

void riemann_events_free(riemann_event_t **evts, size_t n_events)
{
        int i;
       
        for (i = 0; i < n_events; i++) {
                riemann_event_free(evts[i]);
                xfree(evts[i]);
        }
        xfree(evts);
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

        for (i = 0; i < n_tags; i++) { 
                evtp->tags[i] = strdup(tags[i]);
                if (!evtp->tags[i]) { /* free the already allocated */
                        int j;
                        for (j = 0; j < i; j++)
                                free(evtp->tags[j]);
                        return -2;
                }
        }
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

int riemann_event_set_attributes(riemann_event_t *evtp, const riemann_attribute_pairs_t *apairsp, size_t n_attrs)
{
        int i;
        riemann_attribute_t **attrs = malloc(sizeof(riemann_attribute_t *) * n_attrs);

        if (!attrs)
                return -2;

        for (i = 0; i < n_attrs; i++) {
                attrs[i] = riemann_attribute_alloc();
                if (!attrs[i]) {
                        int j;
                        for (j = 0; j < i; j++)
                                riemann_attribute_free(attrs[i]); 
                        return -1;
                }
                
                riemann_attribute_init(attrs[i]);
                riemann_attribute_set_key(attrs[i], apairsp[i].key);
                riemann_attribute_set_value(attrs[i], apairsp[i].value);
        }
        evtp->attributes = attrs;
        evtp->n_attributes = n_attrs;
        return 0;
}

int riemann_event_strfevent(char *s, size_t max, const char *fmt, riemann_event_t *evtp)
{
        int offset;
        int bytes;

        assert(s);
        assert(max > 0);
        assert(fmt);
        assert(evtp);

        for (offset = 0; offset < max && *fmt; offset++, fmt++) {
                if (*fmt == '%') {
                        int i;
                        switch (*++fmt) {
                        case 'T':
                                if (!evtp->has_time)
                                        bytes = snprintf(s + offset, max - offset, "%s", "");
                                else 
                                        bytes = snprintf(s + offset, max - offset, "%" PRId64, evtp->time);

                                if (bytes < 0)
                                        return -1;
                                offset += bytes - 1;
                                break;
                        case 'c':
                                if (!evtp->has_time)
                                        bytes = snprintf(s + offset, max - offset, "%s", "");
                                else 
                                        bytes = snprintf(s + offset, max - offset, "%s", ctime((time_t *) &evtp->time));

                                if (bytes < 0)
                                        return -1;
                                offset += bytes - 2;

                                break;
                        case 'S':
                                bytes = snprintf(s + offset, max - offset, "%s", evtp->state);
                                if (bytes < 0)
                                        return -1;

                                offset += bytes - 1;
                                break;
                        case 's':
                                bytes = snprintf(s + offset, max - offset, "%s", evtp->service);
                                if (bytes < 0)
                                        return -1;

                                offset += bytes - 1;
                                break;
                        case 'h':
                                bytes = snprintf(s + offset, max - offset, "%s", evtp->host);
                                if (bytes < 0)
                                        return -1;

                                offset += bytes - 1; 
                                break;
                        case 'd':
                                bytes = snprintf(s + offset, max - offset, "%s", evtp->description);
                                if (bytes < 0)
                                        return -1;

                                offset += bytes - 1;
                                break;
                        case 'G': /* tags */
                                if (evtp->n_tags > 0) {
                                        for (i = 0; i < evtp->n_tags; i++) {
                                                bytes = snprintf(s + offset, max - offset, "%s,", evtp->tags[i]);
                                                if (bytes < 0)
                                                        return -1;

                                                offset += bytes;
                                        }
                                        offset -= 2; /* remove trailing `,' */
                                } else {
                                        bytes = snprintf(s + offset, max - offset, "%s", "");

                                        if (bytes < 0)
                                                return -1;
                                        offset += bytes - 1;
                                }          
                                break;
                        case 't':
                                if (!evtp->has_ttl)
                                        bytes = snprintf(s + offset, max - offset, "%s", "");
                                else
                                        bytes = snprintf(s + offset, max - offset, "%f", evtp->ttl);

                                if (bytes < 0)
                                        return -1;
                                offset += bytes - 1;
                                break;
                        case 'a':
                                if (evtp->n_attributes > 0) {
                                        for (i = 0; i < evtp->n_attributes; i++) {
                                                bytes = snprintf(s + offset, max - offset, "%s=%s,", 
                                                                 evtp->attributes[i]->key,
                                                                 evtp->attributes[i]->value);
                                                if (bytes < 0)
                                                        return -1;

                                                offset += bytes;
                                        }
                                        offset -= 2; /*  remove trailing `,' */
                                } else {
                                        bytes = snprintf(s + offset, max - offset, "%s", "");

                                        if (bytes < 0)
                                                return -1;
                                        offset += bytes - 1;
                                }
                                break;
                        case 'm':
                                switch (*++fmt) {
                                case 'i':
                                        if (!evtp->has_metric_sint64)
                                                bytes = snprintf(s + offset, max - offset, "%s", "");
                                        else
                                                bytes = snprintf(s + offset, max - offset, "%" PRId64, evtp->metric_sint64);

                                        if (bytes < 0)
                                                return -1;
                                        offset += bytes - 1;
                                        break;
                                case 'd':
                                        if (!evtp->has_metric_d)
                                                bytes = snprintf(s + offset, max - offset, "%s", "");
                                        else
                                                bytes = snprintf(s + offset, max - offset, "%f", evtp->metric_d);

                                        if (bytes < 0)
                                                return -1;
                                        offset += bytes - 1;
                                        break;
                                case 'f':
                                        if (!evtp->has_metric_f)
                                                bytes = snprintf(s + offset, max - offset, "%s", "");
                                        else
                                                bytes = snprintf(s + offset, max - offset, "%f", evtp->metric_f);
                                        if (bytes < 0)
                                                return -1;

                                        offset += bytes - 1;
                                        break;
                                default:
                                        fprintf(stderr, "Unknown flag\n");
                                        exit(EXIT_FAILURE);
                                        break;
                                }
                                break;

                        default:
                                fprintf(stderr, "Unknown flag\n");
                                exit(EXIT_FAILURE);
                                break;
                        }
                } else {
                        s[offset] = *fmt;
                }
        }

        if (offset >= max)  {
                s[max - 1] = '\0';
                return offset;  /* S is not lenghty enough */
        }

        s[offset] = '\0';
        return 0;               /* sucess */
}
