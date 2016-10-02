/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#include "riemann/common.h"
#ifdef RIEMANN_HAVE_ALLOCA_H
# include <alloca.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **strtoknize(const char *str, size_t slen, const char *dlmt, int dlen, int  *n_toks)
{
        char *toks = alloca(slen);
        char *save_ptr = NULL;
        char *ptr = NULL;
        int i;
        char **buffer = NULL;

        strncpy(toks, str, slen);

        if (!strcmp(&toks[slen - dlen], dlmt)) { /* remove trailing delimiters */
                toks[slen - dlen] = '\0';
        }

        i = 0;
        ptr = strtok_r(toks, dlmt, &save_ptr);
        while (ptr) {
                i++;
                buffer = realloc(buffer, sizeof (char **) * i);
                assert(buffer);
                buffer[i - 1] = strdup(ptr);
                assert(buffer[i - 1]);
                ptr = strtok_r(NULL, dlmt, &save_ptr);
        }

        if (n_toks)
                *n_toks = i;

        return buffer;
}

void xfree(void *ptr)
{
        if (ptr) {
                free(ptr);
                ptr = NULL;
        } else  {
                fprintf(stderr, "common.c: Trying to free a NULL pointer");
        }
}

void *xmalloc(size_t len)
{
        void *block = malloc(len);
        if (!block)
                pexit("malloc");
        return block;
}
