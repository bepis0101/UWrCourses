#include <stdio.h>
int T(int n, int m)
{
    if(n == 0)
    {
        return m;
    }
    if(m == 0)
    {
        return n;
    }
    return T(n-1, m) + 2*T(n, m-1);
}
int tab[100000];

int T_nr(int n, int m)
{
    int pom;
    for(int i = 0; i <= m; i++)
    {
        tab[i] = i;
    }

    for(int i = 0; i < n; i++)
    {
        pom = i+1;
        tab[0] = i+1;
        for (int j = 1; j <= m; j++)
        {
            tab[j] += 2*pom;
            pom = tab[j];
        }
    }

    return tab[m];
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", T(n, m));    
    printf("%d\n", T_nr(n, m));
}