/*
*   Borys Adamiak
*   lista 1: zadanie 4
*   gcc tabliczka.c
*/


#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if(a > b) return a;
    return b;
}

int digits_count(float x)
{
    int count = 0;
    while(x >= 1)
    {
        count++;
        x /= 10;
    }
    return count;
}

void arr(float x1, float x2, float y1, float y2, float jump)
{
    int cnt = 3;
    cnt += max(digits_count(x2), digits_count(y2));
    int after_punctuation = 2;
    char c  = ' ';
    printf("%*c", cnt+2, c);
    for(float i = y1; i < y2; i += jump)
    {
        printf("%*.*f ", cnt, after_punctuation, i);
    }
    putchar('\n');
    for(float i = x1; i < x2; i += jump)
    {
        printf("%*.*f: ", cnt, after_punctuation, i);
        for(float j = y1; j < y2; j += jump)
        {
            printf("%*.*f ", cnt, after_punctuation, i*j);
        }
        putchar('\n');
    }

}

int main()
{
    arr(0.2, 15.3, 0.2, 3.14, 0.7);
    putchar('\n');
    arr(0.6, 10, 1, 1.2, 0.05);
    putchar('\n');
    arr(1, 10, 1, 10.9, 1);
}