#include <stdio.h>
unsigned int fib[48] = {0};
void dany_fib(unsigned int fib[])
{
    fib[0] = 0; fib[1] = 1;
    for(int i = 2; i <= 46; ++i)
    {
        fib[i] = fib[i-1]+fib[i-2];
    }
}
int main()
{
    unsigned int x; 
    scanf("%u", &x);
    dany_fib(fib);
    int check = 0;
    for(int i = 46; i > 1; i--)
    {
        if(x >= fib[i])
        {
            printf("1");
            x -= fib[i];
            check = 1;
        }
        else
        {
            if(check == 1)
            {
                printf("0");
            }
        }
    }
}