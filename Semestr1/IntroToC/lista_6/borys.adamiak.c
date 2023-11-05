#include <stdio.h>
#include "operacje.h"
#include "operacje.c"

int main()
{
    char *string = (char*)malloc(sizeof(char)*1000);
    char *next = string;
    scanf("%c", next);
    while(*next != ' ' && *next != '\n')
    {
        next++;
        scanf("%c", next);
    }
    *next = '\0';
    if(palindrom(string))
    {
        printf("PALINDROM: %s", string);
    }
    else
    {
        reverse(string);
    }
    free(string);
}