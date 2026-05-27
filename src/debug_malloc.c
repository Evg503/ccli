#include <stdio.h>
#include <stdlib.h>

void*(*system_malloc)(size_t) = malloc;
void(*system_free)(void*) = free;

#include <debug_malloc.h>

typedef struct malloc_entry {
    void *p;
    size_t size;
    struct malloc_entry *next;
} malloc_entry;

typedef struct malloc_stat {
    size_t current;
    size_t full;
    size_t max;
    malloc_entry *entries;
} malloc_stat;

malloc_stat allocated = {0};

void* evg_malloc(size_t size)
{
    void *p = system_malloc(size);
    printf("Alloc %zu bytes by %p\n", size, p);
    malloc_entry *entry= system_malloc(sizeof *entry);
    entry->next = allocated.entries;
    allocated.entries = entry;
    allocated.current +=size;
    allocated.full +=size;
    if(allocated.max < allocated.current) 
        allocated.max = allocated.current;
    return p;
}

void print_malloc_stats()
{
    printf ("Allocated:%zu\n", allocated.current);
} 

void evg_free(void* p){
    system_free(p);
    printf("Dealloc  %p\n", p);
}
