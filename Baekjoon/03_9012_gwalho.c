#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 52
//길이 50인 문자열 받으려면 51이 최소 필요하다
//개행문자를 없애기 위해서 1이 추가로 필요하므로 52가 최소 필요

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

int is_VPS(char *str)
{
    StackType S;
    init(&S);

    for (int j = 0; j < strlen(str); j++)
    {
        if (str[j] == '(')
            push(&S, str[j]);
        else if (str[j] == ')')
        {
            if (is_empty(&S))
                return 0;
            else
                pop(&S);
        }
    }
    if (is_empty(&S))
        return 1;
    else
        return 0;
}

int main()
{
    int N;
    scanf("%d ", &N);

    char str[MAX_SIZE];

    for (int i = 0; i < N; i++)
    {
        fgets(str, MAX_SIZE, stdin);
        //여기서 strlen로 하면 안됩니다!
        //strlen함수는 NULL이 나올때까지 센다!
        str[strlen(str) - 1] = '\0';
        //그래서 마지막 개행문자를 NULL로 바꾸어주면 strlen는 -1

        if (is_VPS(str) == 0)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}