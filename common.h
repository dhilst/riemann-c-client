#include <stdio.h>
#include <stdlib.h>

#define pexit(s) \
do {						\
	perror(s);				\
	exit(EXIT_FAILURE);			\
} while (0)

void *xmalloc(size_t len);
