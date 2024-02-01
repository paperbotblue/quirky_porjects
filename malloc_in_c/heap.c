#include "./heap.h"

#define HEAP_CAP 640000
static uintptr_t heap[HEAP_CAP] = {0}; 

// this premain function is compiler specific 
void __attribute__ ((constructor)) premain()
{
    if(HEAP_CAP % sizeof(uintptr_t) != 0) 
    {
        printf("[+]Error in file: %s line: %d\nThe heap capacity is not divisible by the size of the pointer of platform x86 64\n",__FILE__,__LINE__);while(1){};
    }
}

#define true 1
#define false 0
#define CHUNK_LIST_CAP 1024

typedef struct 
{
    uintptr_t* start;
    size_t size;
}Chunk;
typedef struct
{
    size_t count;
    Chunk chunks[CHUNK_LIST_CAP];
} Chunk_List;

static Chunk_List alloced_chunks = {0};
static Chunk_List freed_chunks = {
    .count = 1,
    .chunks = {
        [0] = {.start = heap, .size = sizeof (heap)}
    },
};
static Chunk_List tmp_chunk = {0};

static void chunk_list_insert(Chunk_List* list, void* start, size_t size);

static void chunk_list_merge( Chunk_List* dst,const Chunk_List* src)
{
    dst->count = 0;
    for(size_t i = 0; i < src->count ; ++i)
    {
        const Chunk chunk = src->chunks[i];
        if(dst->count > 0)
        {   
            Chunk* top_chunk = &dst->chunks[dst->count - 1];
            
            if(top_chunk->start + top_chunk->size == chunk.start)
            {
                top_chunk->size += chunk.size;
            }
            else
            {
                chunk_list_insert(dst,chunk.start,chunk.size);
            }
        }
        else
        {
            chunk_list_insert(dst,chunk.start,chunk.size);
        }
    }
}

static void chunk_list_dump(const Chunk_List* list)
{
    printf("Chunks(%zu):\n",list->count);
    for(size_t i = 0 ; i < list->count ; ++i)
    {
        printf("start: %p, size: %zu\n",
        (void*)list->chunks[i].start,
        list->chunks[i].size);
    }
}

static int chunk_start_compar(const void *a,const void *b)
{
    const Chunk *a_chunk = a;
    const Chunk *b_chunk = b;
    return a_chunk->start - b_chunk->start;
}



static int chunk_list_find(const Chunk_List* list,uintptr_t* ptr)
{
    Chunk key = {
        .start = ptr,
    };

    Chunk *result = bsearch(&key,list->chunks,
                            list->count,
                            sizeof(alloced_chunks.chunks[0]),chunk_start_compar);
    if(result != 0) {
        assert(list->chunks <= result);
        return (result - list->chunks) ;
    } else {
        return -1;
    }
}    


static void chunk_list_insert(Chunk_List* list, void* start, size_t size)
{
    assert(list->count < CHUNK_LIST_CAP);
    list->chunks[list->count].start = start;
    list->chunks[list->count].size = size;

    for(size_t i = list->count; 
        i > 0 && list->chunks[i].start < list->chunks[i-1].start;
         --i)
    {
        const Chunk temp = list->chunks[i];
        list->chunks[i] = list->chunks[i-1];
        list->chunks[i-1] = temp; 
    }
    list->count+=1;
}

static void chunk_list_remove(Chunk_List* list,size_t index)
{
    assert(index < list->count);
    for(size_t i = index; i < list->count-1 ; ++i)
    {
        list->chunks[i] = list->chunks[i+1];
    }    
    list->count--;
}

void *heap_alloc(size_t size_bytes)
{
    if(size_bytes > 0){

    const size_t size_word = (size_bytes + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);

    chunk_list_merge(&tmp_chunk, &freed_chunks);
    freed_chunks = tmp_chunk;

    for(size_t i = 0 ; i < freed_chunks.count ; ++i)
    {
        const Chunk chunk = freed_chunks.chunks[i];
        if(chunk.size >= size_word)
        {
            chunk_list_remove(&freed_chunks,i);

            const size_t tail_size = chunk.size - size_word;
            chunk_list_insert(&alloced_chunks, chunk.start, size_word);
            if(tail_size > 0)
            {
                chunk_list_insert(&freed_chunks, chunk.start + size_word,tail_size);
            }
            return chunk.start;
        }
    }
    }
    return NULL;
}



void heap_free(void* ptr)
{
    if(ptr != NULL)
    {
        const int index = chunk_list_find(&alloced_chunks,ptr);
        assert(index >= 0);
        assert(ptr == alloced_chunks.chunks[index].start);
        chunk_list_insert(&freed_chunks,
                            alloced_chunks.chunks[index].start,alloced_chunks.chunks[index].size);
        chunk_list_remove(&alloced_chunks, (size_t) index);
    }
}

void heap_collect()
{
    UNIMPLEMENTED;  
}

void heap_debug()
{
    printf("======ALLOCATED MEM=====\n");
    chunk_list_dump(&alloced_chunks);
    printf("========FREED MEM=======\n");
    chunk_list_dump(&freed_chunks);
}