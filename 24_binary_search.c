#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000000L
int list[MAX_ELEMENTS];
int count; // 수행횟수

int bin_search(int list[], int n, int searchnum)
{
    int left = 0;
    int right = n - 1;
    int middle;

    count = 0;
    while (left <= right)
    {
        count++;
        middle = (left + right) / 2;
        if (searchnum == list[middle])
            return middle;
        else if (searchnum < list[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}

int main()
{
    int i;
    int search_number;
    int return_value;

    for (i = 0; i < MAX_ELEMENTS; i++)
        list[i] = i;

    printf("input number\n", &search_number);
    scanf("%d", &search_number);

    return_value = bin_search(list, MAX_ELEMENTS, search_number);
    printf("%d th found\n", return_value);
    printf("count=%d\n ", count);

    return 0;
}