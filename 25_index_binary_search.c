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

int binary_search(int list[], int left, int right, int searchnum)
{
    int low = left;
    int high = right - 1;
    int middle;

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (list[middle] == searchnum)
            return middle;
        else if (list[middle] < searchnum)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

int index_binary_search(itable list[], int left, int right, int searchnum)
{
    int low = left;
    int high = right - 1;
    int middle;

    while (low <= high)
    {
        middle = (low + high) / 2;
        printf("middle : %d", middle);
        if (searchnum >= list[middle].key && list[middle + 1].key > searchnum)
            return middle;
        else if (list[middle].key < searchnum)
            low = middle + 1;
        else
            high = middle - 1;
    }
    return (right - 1);
}

int index_search(int key)
{
    int low, high;

    int index = index_binary_search(index_list, 0, idx_n, key);
    if (index == idx_n - 1)
    {
        low = index_list[index].index;
        high = n - 1;
    }
    else
    {
        low = index_list[index].index;
        high = index_list[index + 1].index - 1;
    }
    printf("index : %d, low : %d high : %d\n", index, low, high);

    return binary_search(list, low, high, key);
}

int main()
{
    printf("%d\n", index_search(3));
    printf("%d\n", index_search(9));
    printf("%d\n", index_search(15));
    printf("%d\n", index_search(22));
    printf("%d\n", index_search(31));
    printf("%d\n", index_search(55));
    printf("%d\n", index_search(67));
    printf("%d\n", index_search(88));
    printf("%d\n", index_search(91));
}