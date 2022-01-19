#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 30

void insertion_sort(int list[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
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

    insertion_sort(list, MAX_SIZE);

    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    printf("\n");
    return 0;
}