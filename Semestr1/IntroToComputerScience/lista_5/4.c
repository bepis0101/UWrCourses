#include <stdio.h>

int g(int n)
{
    if(n == 1 || n == 2 || n == 0)
    {
        return 1;
    }
    return g(n-1)+g(n-2)+g(n-3);
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", g(n));
}
