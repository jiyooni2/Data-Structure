#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define MAX_SIZE 9

int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    int index = (left + right) / 2;

    pivot = list[index];
    low = left + 1;
    high = right;
    printf("\nleft : %d right : %d index value:%d\n", left, right, list[index]);

    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");

    printf("<init> low : %d high : %d\n", low, high);

    SWAP(list[index], list[left], temp);

    while (low < high)
    {
        while (low <= right && pivot > list[low])
        {
            low++;
        }
        while (high >= (left) && pivot < list[high])
        {
            high--;
        }
        if (low < high)
        {
            printf("<swap>low : %d high : %d\n", low, high);
            SWAP(list[low], list[high], temp);
        }
    }

    SWAP(list[high], list[left], temp);

    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");

    return high;
}

void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

int main()
{
    srand(time(NULL));
    int list[MAX_SIZE] = {5, 3, 8, 4, 9, 1, 6, 2, 7};

    quick_sort(list, 0, MAX_SIZE - 1);
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    return 0;
}