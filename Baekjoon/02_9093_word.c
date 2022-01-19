#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEGNTH 1000
#define MAX_SIZE 20

typedef struct StackType
{
    int top;
    char item[MAX_SIZE];
} StackType;

void init(StackType *S)
{
    S->top = -1;
}

int is_empty(StackType *S)
{
    return (S->top == -1);
}

void push(StackType *S, char str)
{
    S->item[++(S->top)] = str;
}

char pop(StackType *S)
{
    if (is_empty(S))
    {
        fprintf(stderr, "error");
        exit(1);
    }

    return S->item[(S->top)--];
}

void print_stack(StackType *S)
{
    for (int i = 0; i <= S->top; i++)
        printf("%c", S->item[i]);
    printf("\n");
}

int main()
{
    int N;
    scanf("%d ", &N);
    for (int i = 0; i < N; i++)
    {
        StackType S;
        init(&S);
        char sen[1000];
        fgets(sen, sizeof(sen) / sizeof(char), stdin);
        sen[strlen(sen) - 1] = '\0';
        //개행문자 제거!!!! sen을 아무리 받는다 한들, strlen은 NULL이 아닌데까지

        char *word = strtok(sen, " ");
        //word는 " "가 나올때까지를 저장하고 그 자리를 NULL로 채우고 ptr반환
        while (word != NULL)
        {
            for (int i = 0; i < strlen(word); i++)
            {
                push(&S, word[i]);
            }
            while (!is_empty(&S))
            {
                //fgets는 항상 개행문자가 같이 들어가는걸 주의하자!
                printf("%c", pop(&S));
            }
            printf(" ");
            word = strtok(NULL, " ");
            //이 NULL부터 시작하는건, stdin에서 인식한다..?? 모르겠다
            //그 NULL로 채운 pointer부터 다시 " "찾아서 거기까지 return
        }
        printf("\n");
    }
    return 0;
}