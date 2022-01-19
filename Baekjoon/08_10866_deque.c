#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10002

typedef struct Node
{
    int item;
    struct Node *link;
} Node;
typedef struct Deque
{
    Node *front;
    Node *back;
} Deque;

void init(Deque *D)
{
    D->front = D->back = NULL;
}

int is_empty(Deque *D)
{
    return ((D->front == NULL) && (D->back == NULL));
}

void push_front(Deque *D, int item)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->item = item;
    tmp->link = NULL;

    if (is_empty(D))
    {
        D->front = tmp;
        D->back = tmp;
    }
    else
    {
        tmp->link = D->front;
        D->front = tmp;
    }
}

void push_back(Deque *D, int item)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->item = item;
    tmp->link = NULL;

    if (is_empty(D))
    {
        D->front = tmp;
        D->back = tmp;
    }
    else
    {
        D->back->link = tmp;
        D->back = tmp;
    }
}

int pop_front(Deque *D)
{
    if (is_empty(D))
        return -1;

    Node *removed = D->front;

    if (D->front == D->back)
    {
        int tmp = removed->item;
        free(removed);
        init(D);
        return tmp;
    }

    D->front = removed->link;
    int tmp = removed->item;
    free(removed);
    return tmp;
}

int pop_back(Deque *D)
{
    if (is_empty(D))
        return -1;

    Node *removed = D->back;

    if (D->front == D->back)
    {
        int tmp = removed->item;
        free(removed);
        init(D);
        return tmp;
    }

    Node *pre = D->front;
    while (pre->link != D->back)
    {
        pre = pre->link;
        //이중연결리스트로 다시 구현하기
    }
    D->back = pre;
    int tmp = removed->item;
    free(removed);

    return tmp;
}

int size(Deque *D)
{
    Node *tmp = D->front;
    if (is_empty(D))
        return 0;

    int res = 1;
    while (tmp != D->back)
    {
        res++;
        tmp = tmp->link;
    }
    return res;
}

int front(Deque *D)
{
    if (is_empty(D))
        return -1;
    return D->front->item;
}

int back(Deque *D)
{
    if (is_empty(D))
        return -1;
    return D->back->item;
}

int main()
{
    Deque D;
    init(&D);

    int N;
    scanf("%d ", &N);
    for (int i = 0; i < N; i++)
    {
        char inst[20];
        fgets(inst, 20, stdin);
        inst[strlen(inst) - 1] = '\0';

        char *token = strtok(inst, " ");

        if (!strcmp(token, "size"))
            printf("%d\n", size(&D));
        else if (!strcmp(token, "pop_front"))
            printf("%d\n", pop_front(&D));
        else if (!strcmp(token, "pop_back"))
            printf("%d\n", pop_back(&D));
        else if (!strcmp(token, "empty"))
            printf("%d\n", is_empty(&D));
        else if (!strcmp(token, "front"))
            printf("%d\n", front(&D));
        else if (!strcmp(token, "back"))
            printf("%d\n", back(&D));
        else if (!strcmp(token, "push_front"))
        {
            token = strtok(NULL, " ");
            push_front(&D, atoi(token));
        }
        else if (!strcmp(token, "push_back"))
        {
            token = strtok(NULL, " ");
            push_back(&D, atoi(token));
        }
    }
    return 0;
}