#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, int data)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = data;
    p->link = head;
    head = p;
    return head;
}

ListNode *insert(ListNode *head, ListNode *pre, int data)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));

    p->data = data;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode *delete_first(ListNode *head)
{
    if (head == NULL)
        return NULL;
    ListNode *removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode *delete (ListNode *head, ListNode *pre)
{
    ListNode *removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

ListNode *find(ListNode *head, int x)
{
    for (ListNode *tmp = head; tmp != NULL; tmp = tmp->link)
    {
        if (tmp->data == x)
            return tmp;
    }
    return NULL;
}

void print_list(ListNode *head)
{
    for (ListNode *tmp = head; tmp != NULL; tmp = tmp->link)
        printf("%d->", tmp->data);
    printf("NULL\n");
}

ListNode *reverse(ListNode *head)
{
    ListNode *p, *q, *r;

    p = head;
    q = NULL;
    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    return q;
}

int main()
{
    ListNode *head = NULL;
    for (int i = 0; i < 5; i++)
    {
        head = insert_first(head, i);
        print_list(head);
    }

    int x = 7;
    if (find(head, x) != NULL)
    {
        printf("%d find\n", find(head, x)->data);
    }
    else
    {
        printf("Not found\n");
    }

    ListNode *q = reverse(head);

    print_list(q);

    head = reverse(q);
    print_list(head);

    for (int i = 0; i < 5; i++)
    {
        head = delete_first(head);
        print_list(head);
    }
    return 0;
}