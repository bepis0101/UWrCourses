#include <stdio.h>

int main()
{
    int n; scanf("%d", &n);
    int k = 0;
    int tab[10];
    while(n > 0)
    {
        tab[n%10] = 1;
        n /= 10;
    }
    for(int i = 0; i <= 9; i++)
    {
        if(tab[i] == 1)
        {
            k++;
        }
    }
    printf("%d", k);
}