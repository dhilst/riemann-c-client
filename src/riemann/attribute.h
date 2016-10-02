/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#ifndef RIEMANN_ATTRIBUTE_H
# define RIEMANN_ATTRIBUTE_H

#include <riemann/_config.h>
#include <riemann/proto.pb-c.h>

#include <stdio.h>

#if RIEMANN_HAVE_STDLIB_H
# include <stdlib.h>
#endif
#if RIEMANN_HAVE_STRING_H
# include <string.h>
#endif 

struct riemann_attribute_pairs_s {
        char *key, *value;
};
typedef struct riemann_attribute_pairs_s riemann_attribute_pairs_t;


typedef Attribute riemann_attribute_t;

void riemann_attribute_init(riemann_attribute_t *attrp);
riemann_attribute_t *riemann_attribute_alloc(void);
void riemann_attribute_free(riemann_attribute_t *attrp);
void riemann_attribute_set_key(riemann_attribute_t *attrp, char *key);
void riemann_attribute_set_value(riemann_attribute_t *attrp, char *value);
#endif
