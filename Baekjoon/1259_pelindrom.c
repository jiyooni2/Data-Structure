#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 7

typedef struct StackType
{
    int top;
    int item[MAX_SIZE];
} StackType;

void init(StackType *S)
{
    S->top = -1;
}

int is_empty(StackType *S)
{
    return (S->top == -1);
}

void push(StackType *S, int item)
{
    S->item[++(S->top)] = item;
}

int pop(StackType *S)
{
    return (S->item[(S->top)--]);
}

int main()
{
    int N, M, S, E;
    scanf("%d ", &N);

    int num[2000];
    for (int i = 0; i < N; i++)
        scanf(" %d", &num[i]);

    scanf(" %d", &M);
    // M = 100000;
    for (int i = 0; i < M; i++)
    {
        scanf(" %d %d", &S, &E);
        // S = 1;
        // E = 10;
        // //수정

        
        int k = 0;

        k = E - 1;
        int is_true = 0;
        for (int j = S - 1; j <= (int)((E - 1 + S - 1) / 2); j++)
        {
            if (num[k--] != num[j])
            {
                printf("0\n");
                is_true = 1;
                break;
            }
        }
        if (is_true == 0)
            printf("1\n");
    }

    return 0;
}