#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100000

typedef struct StackType
{
    int item[MAX_SIZE];
    int top;
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
    if (is_empty(S))
        return -1;
    return S->item[(S->top)--];
}
int top(StackType *S)
{
    if (is_empty(S))
        return -1;
    return S->item[S->top];
}
int size(StackType *S)
{
    return (S->top) + 1;
}

int main()
{
    StackType S;
    init(&S);

    int N;
    scanf("%d ", &N);

    char instruction[100000];
    for (int j = 0; j < N; j++)
    {
        //fflush(stdin); //텍스트스트림 내용 모두 비움

        fgets(instruction, sizeof(instruction) / sizeof(char), stdin);
        char *token = strtok(instruction, "\n");

        if (strcmp(token, "top") == 0)
        {
            printf("%d\n", top(&S));
        }
        else if (strcmp(token, "size") == 0)
        {
            printf("%d\n", size(&S));
        }
        else if (strcmp(token, "pop") == 0)
        {
            printf("%d\n", pop(&S));
        }
        else if (strcmp(token, "empty") == 0)
        {
            printf("%d\n", is_empty(&S));
        }
        else
        // push인 경우
        {
            token = strtok(token, " ");
            token = strtok(NULL, " ");
            //token=strtok(NULL," ");랑 같음
            //블럭상태에서 이걸 호출하면, 이전에 찾은 구분자 뒤에서부터
            //다시 구분자를 찾음, NULL=\0
            push(&S, atoi(token));
            //atoi() string to int
        }
    }
    return 0;
}