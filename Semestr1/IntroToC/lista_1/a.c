#include <stdio.h>

int main ()
{
    int n;
    scanf("%d" , &n);
    int check = 1; 
    for(int i = n; i <= n+1000; i++)
    {
        check = 1;
        for (int j = 2; j*j < i; j++)
        {
            if(i % (j*j) == 0)
            {
                check = 0;
            }
        }
        if(check == 1)
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("BRAK");
}