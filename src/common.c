#include "riemann/common.h"

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
