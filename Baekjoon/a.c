#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int item[1000000];
int top;

void init(StackType*S)
{
    S->top=-1;
}

void push(StackType*S,int item)
{
    S->item[++(S->top)]=item;
}

int main()
{
    StackType S;
    init(&S);
    printf("ASFDSA");
    return 0;
}