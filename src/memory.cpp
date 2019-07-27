#include "memory.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void *nodeparse_malloc(const size_t sz)
{
    if(sz > 0){
        void *mem = malloc(sz);
        assert (mem);
        return mem;
    }
    return NULL;
}

void *nodeparse_malloc_zero(const size_t sz)
{
    void *mem = nodeparse_malloc(sz);
    if(mem){
        memset(mem, 0, sz);
    }
    return mem;
}

void nodeparse_free(void *mem)
{
    if(mem)
        free(mem);
}

void nodeparse_clean(void **mem)
{
    if(mem){
        nodeparse_free(mem);
        *mem = NULL;
    }
}

void *nodeparse_realloc(void *mem, const size_t sz)
{
    if(sz > 0){
        void *new_mem = realloc(mem, sz);
        assert(new_mem);
        return new_mem;
    }
    return NULL;
}
