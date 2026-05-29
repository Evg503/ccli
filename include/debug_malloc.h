#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif
#ifdef realloc
#undef realloc
#endif

#define malloc evg_malloc
#define free evg_free
#define realloc evg_realloc
#define strdup evg_strdup


#define calloc   evg_not_implemented
#define strndup  evg_not_implemented
#define asprintf evg_not_implemented
#define getline  evg_not_implemented
#define getdelim evg_not_implemented
#define realpath evg_not_implemented
 

void* evg_malloc(size_t size);
void evg_free(void* p);
char* evg_realloc(char *s, size_t size);
char* evg_strdup(const char *s);

void print_malloc_stats();
bool check_allocs();

