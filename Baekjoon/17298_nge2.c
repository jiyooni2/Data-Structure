#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 8000002

char arr[MAX_SIZE];

int main()
{
    fgets(arr,MAX_SIZE,stdin);

    arr[strlen(arr)-1]='\0';
    char *token = strtok(arr, " ");

    while (token != NULL)
    {
        insert_last(, atoi(token));
        token = strtok(NULL, " ");
    }


    return 0;
}