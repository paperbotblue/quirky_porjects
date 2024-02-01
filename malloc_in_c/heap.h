#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG true

#if DEBUG == true
    #define assert(x) if(!(x)) \
        {printf("[+]Error in file: %s line: %d\n",__FILE__,__LINE__); while(1){}}
#else
    #define assert(x) x
#endif

#define UNIMPLEMENTED \
    do{ fprintf(stderr,"In file: %s | UNIMPLEMENTED FUNCTION: %s | on line: %d\n",__FILE__,__func__ , __LINE__);\
    abort();\
    }while(0)


typedef unsigned long int	uintptr_t;

void *heap_alloc(size_t size_bytes);
void heap_free(void* ptr);
void heap_collect();
void heap_debug();

#endif // HEAP_H