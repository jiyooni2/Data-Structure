#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100002

typedef struct StackType
{
    int item[MAX_SIZE];
    int top;
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
    return S->item[(S->top)--];
}

int main()
{
    StackType S;
    init(&S);
    char sen[MAX_SIZE];
    int unit = 0;

    fgets(sen, MAX_SIZE, stdin);
    sen[strlen(sen) - 1] = '\0';

    for (int i = 0; i < strlen(sen); i++)
    {
        if (sen[i] == '(' && sen[i + 1] == ')')
        {
            // Laser
            unit = unit + S.top + 1;
            i++;
            //반영됨 매우중요!!!!
            continue;
        }

        if (sen[i] == '(')
        {
            push(&S, 1); //숫자 의미 없음
        }
        if (sen[i] == ')')
        {
            unit++;
            pop(&S);
        }
    }
    printf("%d", unit);

    return 0;
}