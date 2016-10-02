/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
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
