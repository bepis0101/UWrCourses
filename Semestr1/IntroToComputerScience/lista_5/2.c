#include <stdio.h>
int silnia(int x)
{
    if(x == 1) return 1;
    else return x*silnia(x-1);
}

int main(

)
{
    int n; 
    scanf("%d", &n);
    int x = 1, res = 1;
    while (res <= n)
    {
        x++;
        res *= x;
        // printf("%d %d\n", x, silnia);
    }
    x--; printf("%d\n", silnia(x));
    int cnt = 0;
    int pom = n;
    for (int i = x; i > 0; i--)
    {
        while(cnt*silnia(i) <= pom)
        {
            cnt++;
        }
        printf("%d ", cnt-1);
        pom -= (cnt-1)*silnia(i);
        cnt = 0;
        
    }
    
}