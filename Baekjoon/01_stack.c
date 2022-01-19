#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode
{
    int item;
    struct StackNode *link;
} StackNode;

typedef struct StackType
{
    StackNode *top;
} StackType;

void init(StackType *S)
{
    S->top = NULL;
}

int is_empty(StackType *S)
{
    return (S->top == NULL);
}

void push(StackType *S, int item)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    temp->item = item;
    temp->link = S->top;

    S->top = temp;
}

int pop(StackType *S)
{
    if (is_empty(S))
        return -1;

    StackNode *removed = S->top;
    int tmp = removed->item;
    S->top = removed->link;
    free(removed);

    return tmp;
}

int size(StackType *S)
{
    int res = 0;
    for (StackNode *p = S->top; p != NULL; p = p->link)
        res++;
    return res;
}

int top(StackType *S)
{
    if (is_empty(S))
    {
        return -1;
    }
    return S->top->item;
}

void main()
{
    StackType S;
    init(&S);

    int N;
    scanf("%d", &N);
    //여기서 엔터치니까 텍스트 스트림에 엔터값이 남아있게 되고,
    //따라서 뒤 연산에서 첫번째 반복문에서 그걸 읽어가서, 반복문 1번안돌고
    char instruction[100];
    for (int j = 0; j < N; j++)
    {
        //fflush(stdin); //텍스트스트림 내용 모두 비움

        fgets(instruction, sizeof(instruction) / sizeof(char), stdin);
        char *token = strtok(instruction, " \n");
        //이것도 사실상 instruction pointer의 시작점
        //strtok의 작동방식
        //알맞은 구분자를 찾으면 \0(문장의 끝 의미)로 바꿈
        //strtok의 첫번째 반환자는 'Block'
        // printf("%s\n", token);
        // 여기서 enter가 두번 쳐지는 이유는, fgets는 enter도 포함하기 때문

    

        if (strcmp(token, "top") == 0)
        {
            printf("%d", top(&S));
        }
        else if (strcmp(token, "size") == 0)
        {
            printf("size");
            printf("%d", size(&S));
        }
        else if (strcmp(token, "pop") == 0)
        {
            printf("%d", pop(&S));
        }
        else if (strcmp(token, "empty") == 0)
        {
            printf("%d", is_empty(&S));
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

    // for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    // //array length 구하는 법
    // {
    //     printf("%c", a[i]);
    // }
}