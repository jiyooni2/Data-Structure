#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *llink;
    struct Node *rlink;
} Node;

void init(Node *phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(Node *before, int data)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;

    before->rlink->llink = newnode;
    //존나 주의하기!!!!
    before->rlink = newnode;
}

void print_dlist(Node *head)
{
    printf("head->");
    for (Node *temp = head->rlink; temp != head; temp = temp->rlink)
        printf("%d->", temp->data);
    printf("head\n");
}

void ddelete(Node *head, Node *removed)
{
    if (head == removed)
        return;

    printf("%d %d %d\n", removed->llink->data, removed->data, removed->rlink->data);
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
    print_dlist(head);
}

int main()
{
    Node *head = (Node *)malloc(sizeof(Node));
    init(head);

    for (int i = 0; i < 5; i++)
    {
        dinsert(head, i);
        print_dlist(head);
    }

    printf("\ndelete step\n");
    for (int i = 0; i < 5; i++)
    {
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    free(head);
    return 0;
}