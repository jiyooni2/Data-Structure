#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_SIZE 20

typedef struct StackType
{
    int top;
    char stack[MAX_STACK_SIZE];
} StackType;

void init(StackType *S)
{
    S->top = -1;
}

int is_empty(StackType *S)
{
    return (S->top == -1);
}

int is_full(StackType *S)
{
    return (S->top == MAX_STACK_SIZE - 1);
}

void error(char *message)
{
    fprintf(stderr, message);
    exit(-1);
}

void push(StackType *S, int item)
{
    if (is_full(S))
    {
        error("overflow");
    }
    S->stack[++(S->top)] = item;
}

char pop(StackType *S)
{
    // if (is_empty(S))
    // {
    //     error("underflow");
    // }
    return (S->stack[(S->top)--]);
}

void print_stack(StackType *S)
{
    for (int i = 0; i <= S->top; i++)
        printf("%c ", S->stack[i]);
    printf("\n");
}

int main()
{
    char expression[MAX_SIZE];
    StackType S;
    char open_ch;
    init(&S);

    fgets(expression, MAX_SIZE, stdin);

    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == '[' || expression[i] == '(' || expression[i] == '{')
        {
            push(&S, expression[i]);
        }
        else if (expression[i] == ']' || expression[i] == ')' || expression[i] == '}')
        {
            if (is_empty(&S))
                error("Failed");

            open_ch = pop(&S);
            if ((open_ch == '(' && expression[i] == ')') ||
                (open_ch == '[' && expression[i] == ']') ||
                (open_ch == '{' && expression[i] == '}'))
                continue;
            else
            {
                error("not matching");
            }
        }
    }

    if (!is_empty(&S))
    {
        error("failed\n");
    }
    else
    {
        printf("Success");
    }
}