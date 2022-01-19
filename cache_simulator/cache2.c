#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 800
#define SIZE 8192
#define FALSE -1
#define LRU 0
#define FIFO 1
typedef struct cache_buffer
{
    unsigned long blkno;
    struct cache_buffer *next, *prev;
    struct cache_buffer *hash_next, *hash_prev;
} cache_buffer;
int cache_hit = 0;
int count = 0;
int list_num = 0;
void hash_chain_print(cache_buffer *ht[]);
void print_list(cache_buffer *head);
void init_cache_list(cache_buffer *head)
{
    head->next = head;
    head->prev = head;
}
cache_buffer *delete_list(cache_buffer *head)
{
    cache_buffer *removed = head->prev;
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    return removed;
}
void insert_list_first(cache_buffer *head, cache_buffer *node)
{
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}
void print_list(cache_buffer *head)
{
    for (cache_buffer *temp = head->next; temp != head; temp = temp->next)
        printf("%ld->", temp->blkno);
    printf("\n");
}
int hash_function(int key)
{
    return (key % MAX_SIZE);
}
int hash_chain_search(cache_buffer *ht[], cache_buffer *list_head, int blkno,
                      int type)
{
    int hash_value = hash_function(blkno);
    cache_buffer *head = ht[hash_value];
    cache_buffer *temp;
    for (temp = head->hash_next; temp != head; temp = temp->hash_next)
    {
        if (temp->blkno == blkno)
        {
            cache_hit++;
            if (type == LRU)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                insert_list_first(list_head, temp);
            }
            return blkno;
        }
    }
    return FALSE;
}
cache_buffer *hash_chain_add(cache_buffer *ht[], int blkno)
{
    int hash_value = hash_function(blkno);
    cache_buffer *head = ht[hash_value];
    cache_buffer *new = (cache_buffer *)malloc(sizeof(cache_buffer));
    new->hash_next = head->hash_next;
    new->hash_prev = head;
    new->blkno = blkno;
    head->hash_next->hash_prev = new;
    head->hash_next = new;
    return new;
}
void hash_chain_delete(cache_buffer *ht[], cache_buffer *removed)
{
    int blkno = removed->blkno;
    int hash_value = hash_function(blkno);
    removed->hash_prev->hash_next = removed->hash_next;
    removed->hash_next->hash_prev = removed->hash_prev;
    free(removed);
}
int hash_chain(cache_buffer *ht[], cache_buffer *list_head, int blkno, int type)
{
    cache_buffer *new, *removed;
    int key = hash_chain_search(ht, list_head, blkno, type);
    if (key == FALSE)
    {
        new = hash_chain_add(ht, blkno);
        insert_list_first(list_head, new);
        if (list_num < SIZE)
        {
            list_num++;
        }
        else
        {
            removed = delete_list(list_head);
            hash_chain_delete(ht, removed);
        }
    }
    return key;
}
void init(cache_buffer *ht[])
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cache_buffer *temp = malloc(sizeof(cache_buffer));
        temp->hash_next = temp;
        temp->hash_prev = temp;
        ht[i] = temp;
    }
}
void hash_chain_print(cache_buffer *ht[])
{
    cache_buffer *node;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("[%d]->", i);
        for (node = ht[i]->hash_next; node != ht[i]; node = node->hash_next)
            printf("%ld->", node->blkno);
        printf("\n");
    }
}
int main()
{
    cache_buffer *head = (cache_buffer *)malloc(sizeof(cache_buffer));
    cache_buffer *hash_table[MAX_SIZE];
    char buf[11];
    int buf_num;
    FILE *fp;
    float miss_ratio;
    float hit_ratio;
    init(hash_table);
    init_cache_list(head);
    if ((fp = fopen("./test_trace.txt", "r")) == NULL)
    {
        perror("Error");
        exit(-1);
    }
    /* test
    for (int i = 0; i < 500; i++)
    {
    count++;
    int k = i % 102;
    printf("[%d] ", k);
    hash_chain(hash_table, head, k, LRU);
    }
    hash_chain_print(hash_table);
    print_list(head);
    printf("\nresult : %d %d\n", cache_hit, count);
    */
    while ((fgets(buf, 11, fp)) > 0)
    {
        count++;
        buf_num = strtoul(buf, NULL, 10);
        hash_chain(hash_table, head, buf_num, FIFO);
    }
    printf("------------------------Result------------------------\n");
    printf("<FIFO>\n");
    hit_ratio = (float)cache_hit / count;
    miss_ratio = (float)(count - cache_hit) / count;
    printf("hit ratio : %f, miss ratio = %f\n\n", hit_ratio, miss_ratio);
    printf("total access = %d, ", count);
    printf("hit = %d, miss = %d\n", cache_hit, count - cache_hit);
    printf("Hit ratio = %f\n\n", hit_ratio);
    fseek(fp, 0L, SEEK_SET);
    count = 0;
    cache_hit = 0;
    list_num = 0;
    init_cache_list(head);
    init(hash_table);
    while ((fgets(buf, 11, fp)) > 0)
    {
        count++;
        buf_num = strtoul(buf, NULL, 10);
        hash_chain(hash_table, head, buf_num, LRU);
    }
    hit_ratio = (float)cache_hit / count;
    miss_ratio = (float)(count - cache_hit) / count;
    printf("<LRU>\n");
    printf("hit ratio : %f, miss ratio = %f\n\n", hit_ratio, miss_ratio);
    printf("total access = %d, ", count);
    printf("hit = %d, miss = %d\n", cache_hit, count - cache_hit);
    printf("Hit ratio = %f", hit_ratio);
    return 0;
}