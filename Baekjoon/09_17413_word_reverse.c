#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100002

typedef struct Node
{
    char item;
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

void push_front(Deque *D, char item)
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

void push_back(Deque *D, char item)
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

char pop_front(Deque *D)
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

char pop_back(Deque *D)
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

int main()
{
    char sen[MAX_SIZE];
    fgets(sen, MAX_SIZE, stdin);
    sen[strlen(sen) - 1] = '\0';

    Deque D;
    init(&D);

    Deque tmp;
    init(&tmp);

    int length = strlen(sen);
    for (int i = 0; i < length; i++)
        push_back(&D, sen[i]);

    char peek = pop_front(&D);
    while (peek != -1)
    {
        if (peek == '<')
        {
            while (peek != '>')
            {
                printf("%c", peek);
                peek = pop_front(&D);
            }
            printf("%c", peek);
            peek = pop_front(&D);
        }
        else
        {
            int is_space = 0;
            while ((peek != '<') && (peek != -1))
            {
                if (peek == ' ')
                {
                    is_space = 1;
                    peek = pop_front(&D);
                    break;
                }
                push_front(&tmp, peek);
                peek = pop_front(&D); //고정
            }

            char reversed = pop_front(&tmp);
            while (reversed != -1)
            {
                printf("%c", reversed);
                reversed = pop_front(&tmp);
            }
            if (is_space == 1)
                printf(" ");
        }
    }

    return 0;
}