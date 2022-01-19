#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct
{
    int heap[MAX_ELEMENT];
    int heap_size;
} Heap;

void init(Heap *H)
{
    H->heap_size = 0;
}

void insert_heap(Heap *H, int key)
{
    H->heap_size++;
    int i = H->heap_size;

    while ((i != 1) && (key > H->heap[i / 2]))
    {
        H->heap[i] = H->heap[i / 2];
        i = i / 2;
    }
    H->heap[i] = key;
}

int delete_heap(Heap *H)
{
    int item = H->heap[1];
    int parent = 1, child = 2;
    int tmp = H->heap[(H->heap_size)--];
    while (child <= H->heap_size)
    {
        //큰 자식이랑 비교!
        if (H->heap[child] < H->heap[child + 1])
            child = child + 1;
        if (H->heap[child] > tmp)
        {
            H->heap[parent] = H->heap[child];
            //큰자식보다 작으면, 내려가야지
            parent = child;
            child = child * 2;
        }
    }
    H->heap[parent] = tmp;

    return item;
}

void print_heap(Heap *H)
{
    for (int i = 1; i <= H->heap_size; i++)
    {
        printf("%d ", H->heap[i]);
    }
    printf("\n");
}

int main()
{
    Heap H;
    init(&H);

    int list[8] = {23, 56, 11, 9, 56, 99, 27, 34};

    for (int i = 0; i < 8; i++)
        insert_heap(&H, list[i]);

    for (int i = 0; i < 8; i++)
        list[i] = delete_heap(&H);

    for (int i = 0; i < 8; i++)
        printf("%d ", list[i]);
    printf("\n");
}