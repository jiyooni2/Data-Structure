#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 30

void selection_sort(int list[], int n)
{
    int i, j, least, temp;

    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[least])
                least = j;
        }
        SWAP(list[least], list[i], temp);
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

    selection_sort(list, MAX_SIZE);

    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    printf("\n");
    return 0;
}