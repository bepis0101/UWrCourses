#include <stdio.h>

int NWD(int a, int b)
{
    while (b != 0)
    {
        int c = a%b;
        a = b;
        b = c;
    }
    return a;
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("NWD liczb %d i %d to %d\n", a, b, NWD(a,b));
    int nww = (a*b)/NWD(a,b);
    printf("NWW tych liczb to %d", nww);
}