// Borys Adamiak
// zad 1 lista 3

#include <stdio.h>

int main()
{
    char c;
    int zag = 0;
    printf("%d", zag);
    while(c = getchar())
    {
        if (c == EOF)
        {
            return 0; 
        }
        putchar(c);
        if(c == '\n') 
        {
            printf("%d", zag);
        } 
        if(c == '{') zag++;
        if(c == '}') zag--;
        if (zag < 0)
        {
            printf("Nieprawidlowy plik\n");
            return 0;
        }
    }
}