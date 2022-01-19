#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10002

typedef struct QueueType
{
    int front; //비어 있는 부분, pop이 일어남
    int rear;  //삽입이 일어나는 곳
    int item[MAX_SIZE];

} QueueType;

void init(QueueType *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(QueueType *Q)
{
    return (Q->front == Q->rear);
}

int is_full(QueueType *Q)
{
    return (((Q->rear) + 1) % MAX_SIZE == Q->front);
}

void push(QueueType *Q, int item)
{
    if (is_full(Q))
    {
        fprintf(stderr, "error");
        exit(1);
    }
    Q->item[(++(Q->rear)) % MAX_SIZE] = item;
}

int pop(QueueType *Q)
{
    return (Q->item[++(Q->front)]);
}

int size(QueueType *Q)
{
    if (Q->rear >= Q->front)
        return (Q->rear - Q->front);
    else
    {
        return (MAX_SIZE - Q->front - Q->rear);
    }
}

int front(QueueType *Q)
{
    return (Q->item[Q->front + 1]);
}
int back(QueueType *Q)
{
    return (Q->item[Q->rear]);
}

int main()
{
    int N;
    scanf("%d ", &N);
    QueueType Q;
    init(&Q);

    char inst[15];
    for (int i = 0; i < N; i++)
    {
        fgets(inst, sizeof(inst) / sizeof(char), stdin);
        inst[strlen(inst) - 1] = '\0';

        if (!strcmp(inst, "front"))
        {
            if (is_empty(&Q))
                printf("-1\n");
            else
                printf("%d\n", front(&Q));
        }
        else if (!strcmp(inst, "size"))
        {
            printf("%d\n", size(&Q));
        }
        else if (!strcmp(inst, "back"))
        {
            if (is_empty(&Q))
                printf("-1\n");
            else
                printf("%d\n", back(&Q));
        }
        else if (!strcmp(inst, "empty"))
        {
            printf("%d\n", is_empty(&Q));
        }
        else if (!strcmp(inst, "pop"))
        {
            if (is_empty(&Q))
                printf("-1\n");
            else
                printf("%d\n", pop(&Q));
        }
        else
        {
            char *token = strtok(inst, " ");
            token = strtok(NULL, " ");
            push(&Q, atoi(token));
        }
    }

    return 0;
}