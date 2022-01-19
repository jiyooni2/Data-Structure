#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX_SIZE 8000000

int main()
{
    int top = -1;
    int wall_top = -1;

    int N;

    scanf("%d ", &N);
    int *res = (int *)malloc(N * sizeof(int));
    int *stack = (int *)malloc(N * sizeof(int));
    int *wall = (int *)malloc(N * sizeof(int));

    char *arr = (char *)malloc(MAX_SIZE * sizeof(char));
    fgets(arr, MAX_SIZE, stdin);
    arr[strlen(arr) - 1] = '\0';

    char *token = strtok(arr, " ");

    while (token != NULL)
    {
        stack[++(top)] = atoi(token);
        token = strtok(NULL, " ");
    }
    int peek;

    for (int i = 0; i < N; i++)
    {
        int is_find = 0;
        peek = stack[(top)--];
        if (wall_top == -1)
        {
            // wall이 비어있으면,
            wall[++(wall_top)] = peek;
            res[i] = -1; //거꾸로들어간다
            continue;
        }
        int k = wall_top;
        while (k >= 0)
        {
            if (wall[k] > peek)
            {
                res[i] = wall[k];
                is_find = 1;
                wall_top = k;
                wall[++wall_top] = peek;
                break;
            }
            k--;
        }
        if (is_find == 0)
        {
            res[i] = -1;
            wall_top = 0;
            wall[wall_top] = peek;
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        printf("%d ", res[i]);
    }

    return 0;
}