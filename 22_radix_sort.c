#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define BUCKETS 10
#define DIGITS 2

typedef struct
{
    int front;
    int rear;
    int queue[SIZE];
} QueueType;

void init(QueueType *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(QueueType *Q)
{
    return (Q->front == Q->rear);
}

void error(char *message)
{
    fprintf(stderr, message);
    exit(-1);
}

int is_full(QueueType *Q)
{
    return ((Q->rear + 1) % SIZE == Q->front);
}

void enqueue(QueueType *Q, int item)
{
    if (is_full(Q))
        error("full");
    Q->rear = (Q->rear + 1) % SIZE;
    Q->queue[Q->rear] = item;
}

int dequeue(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    Q->front = (Q->front + 1) % SIZE;
    return (Q->queue[Q->front]);
}

int peek(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    return (Q->queue[Q->front]);
}

void print(QueueType *Q)
{
    for (int i = Q->front + 1; i != Q->rear; i = ((i + 1) % SIZE))
        printf("%d->", Q->queue[i]);
    printf("%d\n", Q->queue[Q->rear]);
}

void radix_sort(int list[], int n)
{
    int b, i;
    int factor = 1;
    QueueType queues[BUCKETS];
    for (b = 0; b < BUCKETS; b++)
        init(&queues[b]);

    for (int d = 0; d < DIGITS; d++)
    {
        for (i = 0; i < n; i++)
        {
            printf("%dth %d %d\n", i, (list[i] / factor) % 10, list[i]);
            enqueue(&queues[(list[i] / factor) % 10], list[i]);
        }
        printf("************************\n");

        for (b = i = 0; b < BUCKETS; b++)
            while (!is_empty(&queues[b]))
                list[i++] = dequeue(&queues[b]);

        factor = factor * 10;
    }
}

int main(void)
{
    int list[SIZE] = {28, 93, 39, 81, 62, 72, 38, 26, 11, 15};

    for (int i = 0; i < SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");
    srand(time(NULL));
    radix_sort(list, SIZE);
    for (int i = 0; i < SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");
    return 0;
}