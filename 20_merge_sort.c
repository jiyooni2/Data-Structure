#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 8
int sorted[MAX_SIZE] = {0};

void merge(int list[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    // printf("\n\nin merge, i : %d j : %d k : %d\n", i, j, k);
    // printf("\nbefore sorted\n");
    // for (int l = 0; l < MAX_SIZE; l++)
    //     printf("%d ", sorted[l]);
    while (i <= mid && j <= right)
    {
        if (list[i] < list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i <= mid)
    {
        for (int l = i; l <= mid; l++)
            sorted[k++] = list[l];
    }
    if (j <= right)
    {
        for (int l = j; l <= right; l++)
            sorted[k++] = list[l];
    }

    for (int l = left; l <= right; l++)
        list[l] = sorted[l];

    //    printf("\nafter sorted\n");
    //   for (int l = 0; l < MAX_SIZE; l++)
    //        printf("%d ", sorted[l]);
}

void merge_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main()
{
    int i;
    srand(time(NULL));

    // for (i = 0; i < MAX_SIZE; i++)
    // {
    //     list[i] = rand() % 100;
    // }
    int list[MAX_SIZE] = {27, 10, 12, 20, 25, 13, 15, 22};
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    merge_sort(list, 0, MAX_SIZE - 1);

    printf("\n");
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");
    return 0;
}