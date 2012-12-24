#include "common.h"

void *xmalloc(size_t len)
{
        void *block = malloc(len);
        if (!block)
                pexit("malloc");
        return block;
}
