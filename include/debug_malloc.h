#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

#define malloc evg_malloc
#define free evg_free


void* evg_malloc(size_t size);
void evg_free(void* p);
void print_malloc_stats();

