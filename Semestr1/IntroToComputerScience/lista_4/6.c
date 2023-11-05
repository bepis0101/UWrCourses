#include <stdio.h>

int main()
{
    int n, k;
    printf("Podaj liczbe ktora chcesz sprawdzic czy jest palindromem oraz w jakiej podstawie: ");
    scanf("%d%d", &n, &k);
    int x = n;
    int length = 0;
    int tab[30];
    while (x > 0)
    {
        tab[length] = x%k;
        length++;
        x /= k;
    }
    int i = 0;
    while (i < length/2)
    {
        if(tab[i] != tab[length-i-1])
        {
            printf("Liczba %d nie jest palindromem %d-arnym", n, k);
            return 0;
        }
        i++;
    }
    printf("Liczba %d jest palindromem %d-arnym", n, k);
     
}
