#include <stdio.h>
#include "./heap.h"

#define N 10
void* ptrs[N];

int main()
{
    for(int i = 1 ; i <= N ; ++i)
    {
        ptrs[i] = heap_alloc(i);
    }
    for(int i = 1 ; i <= N ; ++i)
    {
        if(i %2 == 0)
        {
            heap_free(ptrs[i]);
        }
    }

    // chunk_list_dump(&alloced_chunks);
    // printf("===========\n");
    // chunk_list_dump(&freed_chunks);
    
// getchar();

    heap_debug();
    return 0;
}