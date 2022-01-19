#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int list[MAX_SIZE];

void init_list()
{
    for (int i = 0; i < MAX_SIZE; i++)
        list[i] = 7 * i;
}

int seq_search(int key, int low, int high)
{
    for (int i = low; i <= high; i++)
    {
        if (list[i] == key)
            return i;
    }
    return -1;
}

int main()
{
    init_list();
    printf("%dth found\n",seq_search(40, 0, MAX_SIZE));
    printf("%dth found\n",seq_search(700, 0, MAX_SIZE));
    printf("%dth found\n",seq_search(1400, 0, MAX_SIZE));
}