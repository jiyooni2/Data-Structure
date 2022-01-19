#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef struct
{
    int front;
    int rear;
    int queue[MAX_QUEUE_SIZE];
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
    return ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front);
}

void enqueue(QueueType *Q, int item)
{
    if (is_full(Q))
        error("full");
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
    Q->queue[Q->rear] = item;
}

int dequeue(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
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
    for (int i = Q->front + 1; i != Q->rear; i = ((i + 1) % MAX_QUEUE_SIZE))
        printf("%d->", Q->queue[i]);
    printf("%d\n", Q->queue[Q->rear]);
}

int main()
{
    QueueType Q;
    init(&Q);

    enqueue(&Q, 10);

    enqueue(&Q, 20);
    enqueue(&Q, 30);
    enqueue(&Q, 40);

    print(&Q);

    printf("dequeue : %d\n", dequeue(&Q));

    printf("dequeue : %d\n", dequeue(&Q));
    printf("dequeue : %d\n", dequeue(&Q));
    print(&Q);
    return 0;
}