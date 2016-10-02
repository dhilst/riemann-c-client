/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#ifndef RIEMANN_COMMON_H
# define RIEMANN_COMMON_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#define pexit(s) \
do {						\
	perror(s);				\
	exit(EXIT_FAILURE);			\
} while (0)

void xfree(void *ptr);
void *xmalloc(size_t len);
char **strtoknize(const char *str, size_t slen, const char *dlmt, int dlen, int  *n_toks);

#endif
