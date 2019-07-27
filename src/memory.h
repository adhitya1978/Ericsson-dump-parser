#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void *nodeparse_malloc(const size_t sz);

void *nodeparse_malloc_zero(const size_t sz);

void nodeparse_free(void *mem);

void nodeparse_clean(void **mem);

void *nodeparse_realloc(void *mem, const size_t sz);


#endif // MEMORY_H
