#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int left(size_t idx)
{
    return (int)(2 * idx + 1);
}

int right(size_t idx)
{
    return (int)(2 * (idx + 1));
}

int parent(size_t idx)
{
    return (int)((idx - 1) / 2);
} 

typedef struct {
    int *arr;
    int tail;
    size_t range;
} Heap;

Heap* init_heap(size_t range)
{
    Heap* heap = malloc(sizeof(Heap));
    heap->arr = calloc(range, sizeof(int));
    heap->tail = -1;
    heap->range = range;

    return heap;
}

void print_heap(Heap* heap)
{
    for(size_t i = 0; i < heap->range; ++i) {
        if(i > heap->tail | heap->tail == -1){
            printf("campo nulo: ");
        }
        else
        {
            printf("campo ok: ");
        }

        printf("%d\n", heap->arr[i]);
    }
    printf("tail = %d\n", heap->tail);
    printf("range = %d\n", heap->range);
}

void realloc_heap(Heap* heap)
{
    size_t new_range = heap->range + 2; 
    int *new_arr = realloc(heap->arr, new_range * sizeof(int));
    memset(new_arr + heap->range, 0, (new_range - heap->range) * sizeof(int));

    heap->arr = new_arr;
    heap->range = new_range;
}

void insert_node(Heap* heap, int val)
{   
    if(heap->tail >= (int)heap->range)
    {
        realloc_heap(heap);
    }

    heap->arr[++heap->tail] = val;
}

void add_arr(Heap* heap, int *arr, size_t arr_count)
{
    for(size_t i = 0; i < arr_count; ++i) {
        insert_node(heap, arr[i]);
    }
}



int main(void)
{
    int arr[8] = {88, 87, 73, 47, 54, 6, 0, 43};
    size_t count = sizeof(arr) / sizeof(arr[0]);
    Heap* heap = init_heap(10);
    add_arr(heap, arr, count);
    print_heap(heap);

    printf("------------\n");

    insert_node(heap, 100);
    print_heap(heap);

    return 0;
}