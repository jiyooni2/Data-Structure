#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100002

typedef struct StackType
{
    int top;
    int item[MAX_SIZE];
} StackType;

void init(StackType *S)
{
    S->top = -1;
}

void push(StackType *S, int item)
{
    S->item[++(S->top)] = item;
}

int pop(StackType *S)
{
    return (S->item[(S->top)--]);
}

int is_empty(StackType *S)
{
    return (S->top == -1);
}

int main()
{
    StackType S;
    init(&S);
    int N;
    scanf(" %d", &N);
    int j;            //수열
    int push_num = 1; //이제 넣어야될 숫자

    char res[MAX_SIZE * 3];
    int res_index = 0;

    for (int i = 0; i < N; i++)
    {
        scanf(" %d", &j);
        for (int k = push_num; k <= j; k++)
        {
            push(&S, k);
            res[res_index] = '+';
            res_index++;
            push_num++;
        }
        int tmp = pop(&S);
        res[res_index] = '-';
        res_index++;
        while (tmp > j)
        {
            tmp = pop(&S);
            res[res_index] = '-';
            res_index++;
        }

        if (tmp != j)
        {
            printf("NO");
            return 0;
        }
    }

    for (int i = 0; i < res_index; i++)
    {
        printf("%c\n", res[i]);
    }

    return 0;
}