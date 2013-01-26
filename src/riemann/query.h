#ifndef RIEMANN_QUERY_H
# define RIEMANN_QUERY_H

#include <riemann/_config.h>
#include <riemann/proto.pb-c.h>

#if RIEMANN_HAVE_STRING_H
# include <string.h>
#endif

typedef Query riemann_query_t;

#define RIEMANN_QUERY_INIT QUERY__INIT

void riemann_query_set_string(riemann_query_t *query, char *string);

#endif
