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
    int n; int a, b;
    scanf("%d", &n);
    scanf("%d", &b);
    for(int i = 1; i < n; i++)
    {
        scanf("%d", a);
        b = NWD(a, b);
    }
    print("%d", b);

}