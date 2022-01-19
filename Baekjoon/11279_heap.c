#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100002

typedef struct Heap
{
    long long heap[MAX_ELEMENT];
    long long heap_size;
} Heap;

void init(Heap *H)
{
    H->heap_size = 0;
}

void insert_heap(Heap *H, int key)
{
    // key가 삽입하려는 key
    int i = ++(H->heap_size);
    // i는 삽입하려는 자리

    while ((i != 1) && (key > H->heap[i / 2]))
    {
        H->heap[i] = H->heap[i / 2]; // swap
        i = i / 2;
    }
    H->heap[i] = key;
}

int delete_max_heap(Heap *H)
{
    if (H->heap_size == 1)
    {
        H->heap_size--;
        return H->heap[1];
    }

    int parent, child;
    int item, temp;

    item = H->heap[1];
    temp = H->heap[(H->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= H->heap_size)
    {
        if ((child < H->heap_size) && (H->heap[child] < H->heap[child + 1]))
            child++;
        if (temp >= H->heap[child])
            break;
        //만족
        H->heap[parent] = H->heap[child];
        //아니면 더 내려감
        parent = child;
        child = child * 2;
    }

    H->heap[parent] = temp;
    return item;
}

void printHeap(Heap *H)
{
    for (int i = 0; i < H->heap_size; i++)
        printf("%d ", H->heap[i]);
    printf("\n");
}

int main()
{
    Heap heap;
    init(&heap);

    int N;
    scanf("%d", &N);

    // insert_heap(&heap, 15);
    // insert_heap(&heap, 11);
    // insert_heap(&heap, 14);
    // insert_heap(&heap, 8);
    // insert_heap(&heap, 10);
    // insert_heap(&heap, 12);
    // insert_heap(&heap, 13);
    // insert_heap(&heap, 2);
    // insert_heap(&heap, 5);
    // insert_heap(&heap, 4);
    // insert_heap(&heap, 9);
    // insert_heap(&heap, 3);
    // insert_heap(&heap, 7);
    // insert_heap(&heap, 6);
    // insert_heap(&heap, 1);

    int left[MAX_ELEMENT];
    int right[MAX_ELEMENT];

    for (int i = 0; i < N; i++)
    {
        right[i] = N;
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", heap.heap[heap.heap_size]);
        delete_max_heap(&heap);
    }

    return 0;
}