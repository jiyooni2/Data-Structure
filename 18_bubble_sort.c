#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define MAX_SIZE 30

void bubble_sort(int list[], int n)
{
    int i, j, temp;
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], temp);
        }
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

    bubble_sort(list, MAX_SIZE);

    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    printf("\n");
    return 0;
}