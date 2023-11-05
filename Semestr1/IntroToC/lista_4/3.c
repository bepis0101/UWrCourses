#include <stdio.h>
#define N 1024

int T[N+3][N+3];

int T_s[N+3][N+3];

int T_d[N+3][N+3];

void snake(int n)
{
    if(n%2 == 0)
    {
        for(int i = 1; i <= n; i += 2)
        {
            for(int j = 1; j <= n; j++)
            {
                T_s[i][j] = T[i][j];
            }
            for(int j = n; j >= 1; j--)
            {
                T_s[i+1][j] = T[i+1][n-j+1];
            }
        }
    }
    else
    {
        for(int i = 1; i < n; i += 2)
        {
            for(int j = 1; j <= n; j++)
            {
                T_s[i][j] = T[i][j];
            }
            for(int j = n; j >= 1; j--)
            {
                T_s[i+1][j] = T[i+1][n-j+1];
            }
        }
        for(int j = 1; j <= n; j++)
        {
            T_s[n][j] = T[n][j];
        }
    }
}

void diagonal(int n)
{
    
}

int main() 
{
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &T[i][j]);
        }
    }
    snake(n);
    for(int i = 0; i <= n+1; i++)
    {
        T[0][i] = -1; T_d[0][i] = -1; T_s[0][i] = -1;
        T[i][0] = -1; T_d[i][0] = -1; T_s[i][0] = -1;
        T[i][n+1] = -1; T_s[i][n+1] = -1; T_d[i][n+1] = -1;
        T[n+1][i] = -1; T_d[n+1][i] = -1; T_s[n+1][i] = -1;
    }

    for (int i = 0; i <= n+1; i++)
    {
        for (int j = 0; j <= n+1; j++)
        {
            printf("%4d", T_s[i][j]);
        }
        printf("\n");
    }
    
}