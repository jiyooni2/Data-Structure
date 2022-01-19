#include <stdio.h>

#define MAX_SIZE 1000
#include <time.h>
int list[MAX_SIZE];

void init_list()
{
    int i;

    for (i = 0; i < 1000; i++)
        list[i] = 7 * i;
}

int search_interpolation(int key, int left, int right)
{
    int low, high, j;
    low = left;
    high = right - 1;
    while (list[low] <= key && list[high] >= key)
    {
        j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low;
        printf("j : %d\n", j);
        printf("low : %d high : %d\n", low, high);
        if (key == list[j])
            return j;
        else if (key < list[j])
            high = j - 1;
        else
            low = j + 1;
    }
    return -1;
}

int main()
{
    init_list();
    printf("%dth found\n ", search_interpolation(140, 0, MAX_SIZE));

    printf("%dth found\n ", search_interpolation(2100, 0, MAX_SIZE));
    printf("%dth found\n ", search_interpolation(4900, 0, MAX_SIZE));
    printf("%dth found\n ", search_interpolation(4905, 0, MAX_SIZE));
    return 0;
}