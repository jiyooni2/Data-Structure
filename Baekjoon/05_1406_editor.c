#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 600002

typedef struct StackType
{
    int top;
    char text[MAX_SIZE];
} StackType;

void push(StackType *S, char item)
{
    S->text[++(S->top)] = item;
}

void init(StackType *S)
{
    S->top = -1;
}

char pop(StackType *S)
{
    return (S->text[(S->top)--]);
}

int is_empty(StackType *S)
{
    return (S->top == -1);
}

int main()
{
    StackType before; //cursor이전
    StackType after;  //cursor이후
    init(&before);
    init(&after);

    char init_text[MAX_SIZE];
    fgets(init_text, MAX_SIZE, stdin);

    int length = strlen(init_text);
    //for문 안에서 strlen을 쓰면, 시간복잡도가 증가할 수 있음
    //최적화 안해줘서..시발뭐이딴게있어

    for (int i = 0; i < length - 1; i++)
    {
        //개행문자 빼고 삽입
        push(&before, init_text[i]);
    }

    int N;
    scanf("%d ", &N);

    for (int i = 0; i < N; i++)
    {
        char text[10];
        fgets(text, 10, stdin);
        // text[strlen(text) - 1] = '\0';
        //NULL과 띄어쓰기는 엄연히 다르다!

        char *token = strtok(text, "\n");
        if (!strcmp(token, "L"))
        {
            if (!is_empty(&before))
            {
                push(&after, pop(&before));
            }
        }
        else if (!strcmp(token, "D"))
        {
            if (!is_empty(&after))
            {
                push(&before, pop(&after));
            }
        }
        else if (!strcmp(token, "B"))
        {
            if (!is_empty(&before))
                pop(&before);
        }
        else
        {
            token = strtok(token, " ");
            token = strtok(NULL, " ");
            //printf("%c",token[0]);
            push(&before, token[0]);
        }
    }

    for (int i = 0; i <= before.top; i++)
        printf("%c", before.text[i]);
    for (int j = after.top; j >= 0; j--)
        printf("%c", after.text[j]);

    return 0;
}