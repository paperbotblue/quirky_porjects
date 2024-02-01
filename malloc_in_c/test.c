#include <stdio.h>
#define FALSE 1
#define TRUE 0
#define word __int32_t
#define UNUSED(x) (void)x
#define ASSERT(x) if(!(x)) {printf("Error in file: %s\nIn function: %s\nAt line: %d\n",__FILE__,__func__,__LINE__);*(int*)0 = 0;}

#define MAX_HEAP_SIZE 64000
#define MAX_CHUNK_ALLOC 1024
word heap[MAX_HEAP_SIZE];

typedef struct
{
  void* ptr;
  word size;
}Chunk;

typedef struct 
{
  size_t size;
  Chunk chunks[MAX_CHUNK_ALLOC];
}Chunk_List;

Chunk_List global_alloc_chunk_list = {0};
Chunk_List global_freed_chunk_list = {
  .size = 1,
  .chunks = {
    [0] = {.ptr = heap, .size = sizeof(heap)}
  }
};

void chunk_list_insert(Chunk_List* chunk_list,Chunk chunk)
{
  chunk_list->chunks[chunk_list->size] = chunk;  
  for(size_t i = chunk_list->size ; chunk_list->chunks[i].size < chunk_list->chunks[i-1].size && i > 0 ; --i)
  {
    Chunk temp = chunk_list->chunks[i-1];
    chunk_list->chunks[i-1] = chunk_list->chunks[i];
    chunk_list->chunks[i] = temp;
  }
  ++chunk_list->size;
}

void* heap_alloc(size_t alloc_size)
{
  if(alloc_size == 0) return NULL;
  word size = (alloc_size + sizeof(word)-1)/sizeof(word);
  ASSERT(size+global_alloc_chunk_list.size < MAX_CHUNK_ALLOC);

  void* ptr = global_freed_chunk_list.chunks[0].ptr;
  global_freed_chunk_list.chunks[0].ptr = (__uint8_t*)global_freed_chunk_list.chunks[0].ptr + (size*sizeof(word));
  global_freed_chunk_list.chunks[0].size -= size;

  chunk_list_insert(&global_alloc_chunk_list, (Chunk){ptr, size});
  return ptr;
}

size_t binary_search(Chunk chunks[],void* key ,size_t left, size_t right)
{
  size_t mid = (left + (right-left)) / 2;
  if(chunks[mid]->ptr == key)
  {
    return mid;
  }
  else if ((__uint8_t*)chunks[mid]->ptr - (__uint8_t*)key > 0)
  {
    binary_search(chunks, key, left, mid - 1);
  }
  else
  {
    binary_search(chunks, key, mid + 1, right);
  }
}

void heap_free(void* ptr)
{
  size_t index = binary_search(&global_alloc_chunk_list.chunks, ptr, 0, global_alloc_chunk_list.size);
  printf("%ld------",index);
}

void print_heap()
{
  printf("==========ALLOCATED==========\n");
  for(size_t i = 0 ; i < global_alloc_chunk_list.size ; ++i)
  {
    printf("%p [SIZE]%d\n",global_alloc_chunk_list.chunks[i].ptr,global_alloc_chunk_list.chunks[i].size);
  }
  printf("============FREED============\n");
  for(size_t i = 0 ; i < global_freed_chunk_list.size ; ++i)
  {
    printf("%p [SIZE]%d\n",global_freed_chunk_list.chunks[i].ptr,global_freed_chunk_list.chunks[i].size);
  }
}

int main()
{
  int MAX = 15;
  char* arr[MAX];
  for(size_t i = 0 ; i < MAX ; ++i)
  {
    arr[i] = heap_alloc(i);
    if(i % 2 == 0)
    {
      
    }
  }
  int* a = heap_alloc(100);
  heap_free(a);
  print_heap();
  return 0;
}