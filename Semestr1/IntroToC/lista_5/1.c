#include <stdio.h>

void SpiralaWiersz(int n, int k)
{
    if(n%2 == 0)
    {
        if (k == 1)
        {
            for(int i = 0; i < n; i++) printf("%4d", n*n - 3*n + i + 3);
        }
        else if(n == k)
        {
            for(int i = 0; i < n; i++) printf("%4d", n*n - i);
        }
        else
        {
            printf("%4d", n*n - 3*n - k + 4);
            SpiralaWiersz(n-2, k-1);
            printf("%4d", n*n - 2*n + 1 + k);
        }
    }    
    else
    {
        if(k == 1)
        {
            for(int i = 0; i < n; i++)
            {
                printf("%4d", n*n - n + 1 + i);
            }
        }
        else if (k == n)
        {
            for(int i = 0; i < n; i++)
            {
                printf("%4d", n*n - 2*n + 2 - i);
            }
        }
        else
        {
            printf("%4d", n*n - n + 2 - k);
            SpiralaWiersz(n-1, k-1);
        }
    }
}

int main(int argc, char *argv[])
{
    int N = 12;
    if (argc > 1) N = atoi(argv[1]);
        
    for(int i = 1; i <= N; i++)
    {
        SpiralaWiersz(N, i);
        printf("\n");
    }
}