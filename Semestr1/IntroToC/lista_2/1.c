// Borys Adamiak
// zadanie 1 lista 2

#include <stdio.h>


int NumGet(int baza)

{
    int liczba[2000000];
    int i = 0;
    char c;
    while(c != '.')
    {
        c = getchar();
        if(c - '0' < baza && c >= '0')
        {
            liczba[i] = c - '0';
            i++;
        }
    }
    int n = i;
    int pow = 1;
    int res = 0;
    for(int j = n; j >= 0; j--)
    {
        res += pow*liczba[j];
        pow *= baza;
    }
    return res/baza;

}
void NumPut(int baza, int x)
{
    int liczba[2000000];
    int i = 0;
    liczba[0] = x%baza;
    x /= baza;
    while(x > 0)
    {
        i++;
        liczba[i] = x%baza;
        x /= baza;
    }
    while(i >= 0)
    {
        putchar(liczba[i]+'0');
        i--;
    }
}
int main()
{
    int base;
    printf("Podaj system w jakim chcesz aby odczytany byl twoj ciag znakow (zakres 2 - 10): \n");
    scanf("%d", &base);
    printf("Teraz podaj ciag znakow: ");
    int x = NumGet(base);
    printf("\nOdczytana liczba w systemie dwojkowym: ");
    NumPut(2, x);
    printf("\nOdczytana liczba w systemie osemkowym: ");
    NumPut(8, x);
    printf("\nOdczytana liczba w systemie dziesietnym: ");
    NumPut(10, x);
    printf("\n");
    

}
