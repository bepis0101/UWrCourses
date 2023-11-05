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
    int c = a/NWD(a,b), d = b/NWD(a,b);

    printf("Ulamek nieskracalny z ilorazu %d/%d to %d/%d", a, b, c, d);
}