#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7

typedef struct
{
    int key;
} element;

typedef struct list
{
    element item;
    struct list *link;
} List;

int hash_function(int key)
{
    return (key % TABLE_SIZE);
}

void hash_chain_add(element item, List *ht[])
{
    int hash_value = hash_function(item.key);

    printf("%d hash_value\n", hash_value);
    List *head = ht[hash_value];
    List *temp;
    for (temp = head; temp->link != NULL; temp = temp->link)
    {
        if (temp->item.key == item.key)
        {
            printf("duplicated\n");
            return;
        }
    }

    List *newnode = malloc(sizeof(List *));
    newnode->item = item;
    newnode->link = NULL;
    printf("new node : %d\n", newnode->item.key);
    printf("last node : %d\n", temp->item.key);

    temp->link = newnode;
}

void hash_chain_search(element item, List *ht[])
{
    int hash_value = hash_function(item.key);
    for (List *node = ht[hash_value]; node != NULL; node = node->link)
    {
        if (node->item.key == item.key)
        {
            printf("Found\n");
            return;
        }
    }
    printf("Not found\n");
}

void hash_chain_print(List *ht[])
{
    List *node;
    int i;
    printf("\n===============================\n");
    for (i = 0; i < TABLE_SIZE; i++)
    {
        printf("[%d]->", i);
        for (node = ht[i]->link; node; node = node->link)
        {
            printf("%d->", node->item.key);
        }
        printf("\n");
    }
    printf("===============================\n");
}

#define SIZE 5
int main()
{
    List *hash_table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        element a;
        a.key = 0;
        List *e = malloc(sizeof(List *));
        e->item = a;
        e->link = NULL;
        hash_table[i] = e;
    }

    int data[SIZE] = {8, 1, 9, 6, 13};
    element e;

    for (int i = 0; i < SIZE; i++)
    {
        e.key = data[i];
        hash_chain_add(e, hash_table);
    }
    hash_chain_print(hash_table);

    for (int i = 0; i < SIZE; i++)
    {
        e.key = data[i];
        hash_chain_search(e, hash_table);
    }
}