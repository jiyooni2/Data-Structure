#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000
#define INDEX_SIZE 10

int list[MAX_SIZE] = {3, 9, 15, 22, 31, 55, 67, 88, 91};
int n = 9;
typedef struct
{
    int key;
    int index;
} itable;

itable index_list[INDEX_SIZE] = {{3, 0}, {22, 3}, {67, 6}};
int idx_n = 3;

int seq_search(int key, int low, int high)
{
    int i;
    for (i = low; i <= high; i++)
        if (list[i] == key)
            return i;
    return -1;
}
int index_search(int key)
{
    int i, low, high;

    for (i = 0; i < idx_n; i++)
    {
        if (index_list[i].key <= key && key < index_list[i + 1].key)
        {
            low = index_list[i].index;
            high = index_list[i + 1].index - 1;
            break;
        }
        if (i == idx_n - 1)
        {
            low = index_list[i - 1].index;
            high = n - 1;
        }
    }
    return seq_search(key, low, high);
}

int main()
{
    printf("%d\n", index_search(88));
}