#include <stdio.h>
#include <string.h>
#define INT_MAX 2147483647
#define N 1000

int sumy[N];
int ile_liter[26][N];

int main()
{
    int n, k;
    int maks = scanf("%d%d", &n, &k);
    char id[n][k];
    int index = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < k; j++)
        {
            char c;
            c = getchar(); 
            while(c < 'a' || c > 'z')
            {
                c = getchar();
            }
            id[i][j] = c;
        }
    }

    for(int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
           ile_liter[id[j][i]-'a'][i]++;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if(ile_liter[id[i][j]-'a'][j] == 1)
            {
                sumy[i]++;
            }
        }
    }
    maks = 0;
    for(int i = 0; i < n; i++) // wyznaczamy maksimum
    {
        if(maks < sumy[i])
        {
            maks = sumy[i];
        }
    }
    for(int i = 0; i < n; i++) // szukanie indeksu
    {
        if(maks == sumy[i])
        {
            index = i; 
            break;
        }
    }
    for(int i = 0; i < k; i++)
    {
        printf("%c", id[index][i]);
    }
    printf("\n%d", maks);


    printf("\n");
    return 0;
}