#include <stdio.h>
#define N 1000
#define INT_MAX 100000000
int tab[N+2];
void bubble_sort(int n)
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(tab[j] > tab[j+1])
            {
                int x = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = x;
            }
        }
    }
}

int main()
{
    int n; scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    bubble_sort(n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");

}