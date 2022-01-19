#include <stdio.h>
#include <stdlib.h>

void main()
{
    char **c = (char **)malloc(50 * sizeof(char *));
    c[0] = "cat";
    c[1] = "fuck";

    printf("%s", *c);
}