#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '0'},
    {'1', '0', '1', '0', '1', '0'},
    {'1', '0', '1', '0', '1', '0'},
    {'1', '0', '0', '0', '1', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

typedef struct
{
    int r;
    int c;
} element;

typedef struct StackType
{
    int top;
    element stack[MAX_STACK_SIZE];
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

void push(StackType *S, int x, int y)
{
    if (is_full(S))
    {
        error("overflow");
    }
    element tmp;
    tmp.r = x;
    tmp.c = y;
    S->stack[++(S->top)] = tmp;
}

element pop(StackType *S)
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
        printf("(%d,%d) ", S->stack[i].r, S->stack[i].c);
    printf("\n");
}

void push_loc(StackType *S, int r, int c)
{
    if (r < 0 || c < 0 || r > MAZE_SIZE || c > MAZE_SIZE)
        return;

    if (maze[r][c] == '0' || maze[r][c] == 'x')
        push(S, r, c);
}

int main()
{
    int r, c;
    StackType S;
    init(&S);

    element here = {1, 0}, entry = {1, 0};

    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }

    here = entry;
    while (maze[here.r][here.c] != 'x')
    {

        maze[here.r][here.c] = '.';

        for (int i = 0; i < MAZE_SIZE; i++)
        {
            for (int j = 0; j < MAZE_SIZE; j++)
                printf("%c", maze[i][j]);
            printf("\n");
        }

        push_loc(&S, here.r - 1, here.c);
        push_loc(&S, here.r + 1, here.c);
        push_loc(&S, here.r, here.c + 1);
        push_loc(&S, here.r, here.c - 1);

        print_stack(&S);

        if (is_empty(&S))
        {
            printf("failed\n");
            return 0;
        }
        else
            here = pop(&S);
    }

    printf("r = %d c = %d success\n", here.r, here.c);
    return 0;
}