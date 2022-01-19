#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define MAX_SIZE 9

int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    pivot = list[left];
    low = left;
    high = right + 1;
    //먼저 left 증가시키고 high는 감소시키고 시작하니까,
    // left, right+1로 두네...

    do
    {
        do
        {
            low++;
        } while (low <= right && list[low] < pivot);
        do
        {
            high--;
        } while (high >= left + 1 && list[high] > pivot);
        if (low < high)
            SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    printf("\n left : %d, right : %d\n", left, right);
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

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

    printf("\n");
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);

    return 0;
}