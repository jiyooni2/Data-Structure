#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13

#define is_empty(item) (strlen(item.key) == 0)
#define is_equal(item1, item2) (!strcmp(item1.key, item2.key))

typedef struct
{
    char key[KEY_SIZE];
} element;

element hash_table[TABLE_SIZE];

void init_table(element ht[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
        ht[i].key[0] = '\0';
}

int transform(char *key)
{
    int number = 0;
    while (*key)
        number = number + *key++;
    return number;
}

int hash_function(char *key)
{
    return transform(key) % TABLE_SIZE;
}

void hash_lp_add(element item, element ht[])
{
    int i, hash_value;
    hash_value = i = hash_function(item.key);

    //빈 자리 찾아나가는 과정
    while (!is_empty(ht[i]))
    {
        if (is_equal(item, ht[i]))
        {
            printf("duplicated key\n");
            return;
        }
        i = (i + 1) % TABLE_SIZE;

        if (i == hash_value)
        {
            printf("full");
            return;
        }
    }
    ht[i] = item;
}

void hash_lp_search(element item, element ht[])
{
    int i, hash_value;
    i = hash_value = hash_function(item.key);

    while (!is_empty(ht[i]))
    {
        if (is_equal(ht[i], item))
        {
            printf("%s(hash value : %d) find\n", item.key, i);
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        if (i == hash_value)
        {
            printf("Not found\n");
            return;
        }
    }
    printf("Not found\n");
}

void hash_qp_add(element item, element ht[])
{
    int i, hash_value;
    i = hash_value = hash_function(item.key);
    int k = 1;
    while (!is_empty(ht[i]))
    {
        if (is_equal(ht[i], item))
        {
            printf("duplicated\n");
            return;
        }

        i = (i + k * k) % TABLE_SIZE;
        k++;

        if (i == hash_value)
            printf("full");
        //여기서 full이라고 하는 건 그냥 한 거라고 생각하자..
        //무한정 loop를 돌 수는 없으니
    }
    ht[i] = item;
}

void hash_qp_search(element item, element ht[])
{
    int i, hash_value;
    i = hash_value = hash_function(item.key);
    int k = 1;
    while (!is_empty(ht[i]))
    {
        if (is_equal(ht[i], item))
        {
            printf("Found\n");
            return;
        }
        i = (i + k * k) % TABLE_SIZE;
        k++;
        if (i == hash_value)
        {
            return;
        }
    }

    printf("Not found\n");
}

int hash_function2(char *key)
{
    int number = 0;
    while (*key)
        number = number + *key++;

    return (number + 5) % TABLE_SIZE;
}

void hash_dh_add(element item, element ht[])
{
    int i, hash_value;
    i = hash_value = hash_function(item.key);
    int inc = hash_function2(item.key);

    while (!is_empty(ht[i]))
    {
        if (is_equal(ht[i], item))
        {
            printf("duplicated\n");
            return;
        }
        i = (i + inc) % TABLE_SIZE;
        if (i == hash_value)
        {
            printf("no place found\n");
            return;
        }
    }
    ht[i] = item;
}

void hash_dh_search(element item, element ht[])
{
    int i, hash_value;
    i = hash_value = hash_function(item.key);
    int inc = hash_function2(item.key);
    while (!is_empty(ht[i]))
    {
        if (is_equal(ht[i], item))
        {
            printf("found\n");
            return;
        }
        i = (i + inc) % TABLE_SIZE;

        if (i == hash_value)
        {
            printf("Not found\n");
            return;
        }
    }
}

void hash_lp_print(element ht[])
{
    printf("-----------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d : %s \n", i, ht[i].key);
    printf("-----------------------------\n");
}

int main(void)
{
    char *s[7] = {"do", "for", "if", "case", "else", "return", "function"};
    element e;

    init_table(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_lp_add(e, hash_table);
    }
    hash_lp_print(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_lp_search(e, hash_table);
    }

    init_table(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_qp_add(e, hash_table);
    }
    hash_lp_print(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_qp_search(e, hash_table);
    }

    init_table(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_dh_add(e, hash_table);
    }
    hash_lp_print(hash_table);

    for (int i = 0; i < 7; i++)
    {
        strcpy(e.key, s[i]);
        hash_dh_search(e, hash_table);
    }
    return 0;
}