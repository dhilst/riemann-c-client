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
