#include <stdio.h>

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    int tabn[10] = {}, int tabm[10] = {};
    while(n > 0)
    {
        tab[n%10]++;
        n /= 10;
    }
    while(m > 0)
    {
        tab[m%10]++;
        m /= 10;
    }
    for(int i = 0; i <= 9; i++)
    {
        if (tabn[i] != tabm[i])
        {
            printf('0');
        }
    }
    printf('1');
    
}