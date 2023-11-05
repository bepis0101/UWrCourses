#include <stdio.h>

int main()
{
    int n, k; 
    scanf("%d%d", &n, &k);
    int maks = 0;
    int tab[k];
    int sumy[k];
    for(int i = 0; i < k; i++)
    {
        scanf("%d", &tab[i]);
        int pom = n;
        int suma = 0;
        while(pom%tab[i] == 0)
        {
            suma++;
            pom /= tab[i];
        }
        sumy[tab[i]] = suma;
        if(maks < suma)
        {
            maks = suma;
        }
    }
    printf("%d ", maks);
    for(int i = 0; i < k; i++)
    {
        if(sumy[tab[i]] == maks)
        {
            printf("%d ", tab[i]);
        }
    }
}