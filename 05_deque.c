#include <stdio.h>
#include <stdlib.h>

#define MAX_DEQUE_SIZE 5
typedef struct
{
    int deque[MAX_DEQUE_SIZE];
    int front, rear;
} Deque;

void error(char *message)
{
    fprintf(stderr, message);
    exit(-1);
}

void init(Deque *D)
{
    D->front = D->rear = 0;
}

int is_empty(Deque *D)
{
    return (D->front == D->rear);
}

int is_full(Deque *D)
{
    return (D->front == ((D->rear) + 1) % MAX_DEQUE_SIZE);
}

void add_front(Deque *D, int item)
{
    if (is_full(D))
    {
        error("full");
    }

    D->deque[D->front] = item;
    D->front = (D->front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
}

void add_rear(Deque *D, int item)
{
    if (is_full(D))
        error("full");
    D->rear = ((D->rear) + 1) % MAX_DEQUE_SIZE;
    D->deque[D->rear] = item;
}

int delete_front(Deque *D)
{
    if (is_empty(D))
        error("empty");
    D->front = ((D->front) + 1) % MAX_DEQUE_SIZE;
    return (D->deque[D->front]);
}

int delete_rear(Deque *D)
{
    if (is_empty(D))
        error("empty");
    D->rear = ((D->rear) - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
    return (D->deque[D->rear]);
}

void print(Deque *D)
{
    for (int i = (D->front + 1) % MAX_DEQUE_SIZE; i != D->rear; i = (i + 1) % MAX_DEQUE_SIZE)
        printf("%d->", D->deque[i]);
    printf("%d\n", D->deque[D->rear]);
}

int main()
{
    Deque D;
    init(&D);

    add_front(&D, 10);
    add_rear(&D, 20);
    print(&D);
    add_front(&D, 30);
    add_front(&D, 40);
    print(&D);

    delete_front(&D);
    delete_front(&D);
    delete_front(&D);
    delete_front(&D);

    add_front(&D, 10);
    add_rear(&D, 20);
    print(&D);
    add_front(&D, 30);
    add_front(&D, 40);

    delete_rear(&D);

    delete_rear(&D);
    delete_rear(&D);
    print(&D);
    return 0;
}