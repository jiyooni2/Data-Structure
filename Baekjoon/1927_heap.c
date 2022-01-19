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
    int i = ++(H->heap_size);

    while (i != 1 && key < H->heap[i / 2])
    {
        H->heap[i] = H->heap[i / 2];
        i = i / 2;
    }

    H->heap[i] = key;
}

int delete_heap(Heap *H)
{
    int parent, child;
    int temp;

    int item = H->heap[1];
    temp = H->heap[(H->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= H->heap_size)
    {
        if ((child < H->heap_size) && (H->heap[child] > H->heap[child + 1]))
        {
            child++;
        }
        if (temp <= H->heap[child])
        {
            //여기서 대입하면 whlie loop 안에 들어올 때 처리 못함
            break;
        }
        H->heap[parent] = H->heap[child];
        //매칭됬으면 다음으로 안내려감
        parent = child;
        child = child * 2;
    }
    H->heap[parent] = temp;

    return item;
}

void printHeap(Heap *H)
{
    for (int i = 1; i <= H->heap_size; i++)
        printf("%d ", H->heap[i]);
    printf("\n");
}

int main()
{
    Heap heap;
    init(&heap);

    int N;
    scanf("%d ", &N);

    for (int i = 0; i < N; i++)
    {
        int j;
        scanf("%d", &j);
        if (j == 0)
        {
            if (heap.heap_size == 0)
                printf("0\n");
            else
            {
                int item = delete_heap(&heap);
                printf("%d\n", item);
            }
        }
        else
        {
            insert_heap(&heap, j);
        }
    }

    return 0;
}