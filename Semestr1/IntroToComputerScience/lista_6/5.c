#include <stdio.h>
#include <stdbool.h>
#define N 1000000
bool sito[N+2];
int main() 
{
    int n; scanf("%d", &n);
    for(int i = 2; i*i <= n; i++)
    {
        if(sito[i] == 0)
        {
            for(int j = 2; j <= n; j++)
            {
                sito[i*j] = true;
            }
        }
    }

    for(int i = 2; i <= n; i++)
    {
        printf("%d %d\n", i, sito[i]);
    }
}