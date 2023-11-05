// Borys Adamiak (oddawane na lekcji z malymi poprawkami)
// Lista 4 Zadanie 1

#include <stdio.h>
typedef unsigned int TypDaty;

char dni_tyg[][7] = {"pon", "wto", "sro", "czw", "pia", "sob", "nie"};
char miesiac[][12] = {"styczen", "luty", "marzec", "kwiecien", "maj", "czerwiec", "lipiec", "sierpien", "pazdziernik", "listopad", "grudzien"};
char rok[][12] = {"malpy", "koguta","swini", "szczura", "tygrysa", "krolika", "smoka", "weza", "konia", "owcy", "kozy", "psa"};
int liczba_dni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


TypDaty dzien(TypDaty x)
{
    x &= 7;
    if (x > 7 || x < 1)
    {
        return 0;
    }
    return x;
}
TypDaty d_mies(TypDaty x)
{
    x >>= 3;
    x &= 31;
    if(x < 1 || x  > 31)
    {
        return 0;
    }
    return x;
}
TypDaty nr_mies(TypDaty x)
{
    int t = d_mies(x);
    x >>= 8;
    x &= 15;
    if(liczba_dni[x] < t)
    {
        return 0;
    }
    return x;
}
TypDaty __rok(TypDaty x)
{
    x >>= 12;
    x &= 15;
    if (x < 1 || x > 12)
    {
        return 0;
    }
    return x;
}

int BladDaty(TypDaty x)
{
    if(dzien(x) == 0) return 0;
    if(d_mies(x) == 0) return 0;
    if(nr_mies(x) == 0) return 0;
    if(__rok(x) == 0) return 0;
    return 1;
}

void WypiszDate(TypDaty data)
{
    printf("%s, ", dni_tyg[(dzien(data)-1)]);
    printf("%u ", d_mies(data));
    printf("%s, ", miesiac[nr_mies(data)-1]);
    printf("rok %s(%u)\n", rok[__rok(data)-1], __rok(data));
}

int main() 
{
    TypDaty data;
    scanf("%u", &data);
    while(data != 0 || feof(stdin))
    {
        if(BladDaty(data) == 0)
        {
            printf("Blad daty\n");
        }
        else
        {
            WypiszDate(data);
        }
        scanf("%u", &data);
    }
    return 0;
}