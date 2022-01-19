#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 30

void insertion_sort(int list[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; (j >= first) && (list[j] > key); j = j - gap)
        {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

void shell_sort(int list[], int n)
{
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if (gap % 2 == 0)
            gap++;
        for (i = 0; i < gap; i++)
            insertion_sort(list, i, n - 1, gap);
    }
}

int main()
{
    int i;
    int list[MAX_SIZE];
    srand(time(NULL));

    for (i = 0; i < MAX_SIZE; i++)
    {
        list[i] = rand() % 100;
    }
    shell_sort(list, MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    printf("\n");
    return 0;
}