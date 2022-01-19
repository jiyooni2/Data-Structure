#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5001

typedef struct ListNode
{
    int item;
    struct ListNode *link;
} ListNode;

typedef struct ListType
{
    ListNode *head;
} ListType;

void init(ListType *L)
{
    L->head = NULL;
}

void insert(ListType *L, int item)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->item = item;

    if (L->head == NULL)
    {
        L->head = node;
        node->link = L->head;
    }

    node->link = L->head->link;
    L->head->link = node;
    L->head = node;
}

int main()
{
    int N, K;
    scanf(" %d %d", &N, &K);
    ListType L;
    init(&L);
    for (int i = 1; i <= N; i++)
        insert(&L, i);

    ListNode *start = L.head->link;
    ListNode *pre;
    ListNode *removed;
    int tmp;

    int j = 0;
    printf("<");
    while (j < N - 1)
    {
        pre = start;
        for (int i = 0; i < K - 2; i++)
            pre = pre->link;

        if (K == 1)
            removed = pre;
        else
        {
            removed = pre->link;
        }
        pre->link = removed->link;
        tmp = removed->item;
        free(removed);

        printf("%d, ", tmp);
        start = pre->link;

        j++;
    }
    printf("%d>", start->item);
    return 0;
}