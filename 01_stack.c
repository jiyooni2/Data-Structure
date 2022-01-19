#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct StackType
{
    int top;
    int stack[MAX_STACK_SIZE];
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

int pop(StackType *S)
{
    if (is_empty(S))
    {
        error("underflow");
    }
    return (S->stack[(S->top)--]);
}

void print_stack(StackType *S)
{
    for (int i = 0; i <= S->top; i++)
        printf("%d ", S->stack[i]);
    printf("\n");
}

int main()
{
    StackType S;
    init(&S);

    push(&S, 10);
    push(&S, 20);
    push(&S, 30);
    push(&S, 40);
    push(&S, 50);
    push(&S, 60);
    print_stack(&S);

    printf("pop item : %d\n", pop(&S));
    printf("pop item : %d\n", pop(&S));
    printf("pop item : %d\n", pop(&S));
    print_stack(&S);
}