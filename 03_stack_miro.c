#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

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

int main()
{
    StackType S;
    init(&S);

    element here = {1, 0}, entry = {1, 0};
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1', '1', '1', '1', '1', '1'},
        {'e', '0', '1', '0', '0', '0'},
        {'1', '0', '1', '0', '1', '0'},
        {'1', '0', '1', '0', '1', '0'},
        {'1', '0', '0', '0', '1', 'x'},
        {'1', '1', '1', '1', '1', '1'},
    };

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    push(&S, here.r, here.c);
    while (1)
    {
        here = pop(&S);

        if (maze[here.r][here.c] == 'x')
            break;
        printf("(%d,%d)\n", here.r, here.c);

        maze[here.r][here.c] = '9';
        for (int i = 0; i < 4; i++)
        {
            int xx = here.r + dx[i];
            int yy = here.c + dy[i];

            printf("xx : %d, yy : %d\n", xx, yy);
            if (xx < 0 || xx >= MAZE_SIZE || yy < 0 || yy > MAZE_SIZE || maze[xx][yy] == '1')
            {
                continue;
            }
            else if (maze[xx][yy] == '0' || maze[xx][yy] == 'x')
            {
                push(&S, xx, yy);
                printf("%c,%d,%d pushed\n", maze[xx][yy], xx, yy);
            }
        }
        if (is_empty(&S))
        {
            printf("No route");
            return 0;
        }
    }

    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}