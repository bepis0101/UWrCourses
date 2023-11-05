#include <stdio.h>
#include <math.h>
#include <string.h>
#define N 1000
#define INT_MAX 100000000
int tab[N+2];
int min(int a, int b)
{
    if (a < b) return a;
    return b;
}

void select_sort(int n)
{
    for(int i = 0; i < n; i++)
    {
        int minimum = INT_MAX;
        for(int j = i; j < n; j++)
        {
            minimum = min(minimum, tab[j]);
        }
        for(int j = i; j < n; j++)
        {
            if(minimum == tab[j])
            {
                tab[j] = tab[i];
                tab[i] = minimum;
                break;
            }
        }
        minimum = INT_MAX;
    }
}

int main()
{
    int n; scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    select_sort(n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");

}


