#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void*(*system_malloc)(size_t) = malloc;
void*(*system_realloc)(void*, size_t) = realloc;
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

static void add_stat(void*p, size_t size) {
    malloc_entry *entry= system_malloc(sizeof *entry);
    entry->next = allocated.entries;
    entry->p = p;
    entry->size = size;
    allocated.entries = entry;
    allocated.current +=size;
    allocated.full +=size;
    if(allocated.max < allocated.current) {
        allocated.max = allocated.current;
    }
    printf("Alloc   %9zu bytes by %p\n", size, p);

}
static void remove_stat(void *p)
{    size_t size = 0;
    for(malloc_entry **pentry = &allocated.entries; *pentry; pentry = &(*pentry)->next) {
        if((*pentry)->p == p){
            size = (*pentry)->size;
            malloc_entry *to_free = *pentry;
            *pentry = (*pentry)->next;
            system_free(to_free);
            break;
        }
    }
    allocated.current -= size;
    printf("DeAlloc %9zu bytes by %p\n", size, p);
}
void* evg_malloc(size_t size)
{
    void *p = system_malloc(size);
    add_stat(p, size);
    return p;
}

void print_malloc_stats()
{
    printf("=============================================\n");
    printf ("Allocated:        %5zu\n", allocated.current);
    printf ("max memory usage: %5zu\n", allocated.max);
    printf ("full allocated:   %5zu\n", allocated.full);
    printf("=============================================\n");
    if(!allocated.entries)
    {
        printf("No used blocks!\n");
    } else {
        for(malloc_entry *entry = allocated.entries; entry; entry = entry->next) {
            printf("|0x%p | %15zu bytes |\n", entry->p, entry->size);
        }
    }
    printf("=============================================\n");
} 

char* evg_strdup(const char *s)
{
  size_t len = strlen (s) + 1;
  void *new = evg_malloc (len);

  if (new == NULL)
    return NULL;

  return (char *) memcpy (new, s, len);
}

bool check_allocs()
{
    return allocated.current == 0;
}

void evg_free(void* p){
    system_free(p);
    remove_stat(p);
}

char* evg_realloc(char *s, size_t size){
    void *new_s = system_realloc(s, size);
    if(new_s){
        remove_stat(s);
        add_stat(new_s, size);
    }
    return new_s;
}
