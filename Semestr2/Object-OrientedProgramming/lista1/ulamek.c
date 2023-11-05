/*
*   Borys Adamiak
*   lista 1: zadanie 2
*   gcc ulamek.c -lm
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct Ulamek
{
    int licznik;
    int mianownik;
}Ulamek;

int NWD(int a, int b)
{
	int pom;

  	while(b!=0)
	{
    	pom = b;
    	b = a%b;
    	a = pom;  
  	}
    return a;
}

int min(int a, int b)
{
    if(a > b) return b;
    return a;
}

Ulamek* create_fraction(int a, int b)
{
    int mini = min(a, b);
    for(int i = mini; i > 1; i--)
    {
        if(a%i == 0 && b%i == 0)
        {
            a /= i;
            b /= i;
        }
    }
    Ulamek *new = (Ulamek*)malloc(sizeof(Ulamek));
    new->licznik = a;
    new->mianownik = b;
    return new;
}

void print_fraction(Ulamek* frac)
{
    if(frac->licznik == 0) printf("0\n");
    else if(frac->licznik == frac->mianownik) printf("1\n");
    else printf("%d/%d\n", frac->licznik, frac->mianownik);
}

Ulamek* add(Ulamek* a, Ulamek* b)
{
    int NWW = (a->mianownik)*(b->mianownik)/NWD((a->mianownik), (b->mianownik));
    int nom = (a->licznik*(NWW/a->mianownik)) + (b->licznik*(NWW/b->mianownik));
    Ulamek* temp = create_fraction(nom, NWW);
    return temp;
}
void _add(Ulamek* a, Ulamek* b)
{
    int NWW = (a->mianownik)*(b->mianownik)/NWD((a->mianownik), (b->mianownik));
    int nom = (a->licznik*(NWW/a->mianownik)) + (b->licznik*(NWW/b->mianownik));
    b->licznik = nom;
    b->mianownik = NWW;
}

Ulamek* sub(Ulamek* a, Ulamek* b)
{
    int NWW = (a->mianownik)*(b->mianownik)/NWD((a->mianownik), (b->mianownik));
    int nom = (a->licznik*(NWW/a->mianownik)) - (b->licznik*(NWW/b->mianownik));
    Ulamek* temp = create_fraction(nom, NWW);
    return temp;
}
void _sub(Ulamek* a, Ulamek* b)
{
    int NWW = (a->mianownik)*(b->mianownik)/NWD((a->mianownik), (b->mianownik));
    int nom = (a->licznik*(NWW/a->mianownik)) - (b->licznik*(NWW/b->mianownik));
    b->licznik = nom;
    b->mianownik = NWW;
}

Ulamek* mult(Ulamek* a, Ulamek* b)
{
    int nom = (a->licznik)*(b->licznik);
    int denom = (a->mianownik)*(b->mianownik);
    Ulamek* temp = create_fraction(nom, denom);
    return temp;
}
void _mult(Ulamek* a, Ulamek* b)
{
    int nom = (a->licznik)*(b->licznik);
    int denom = (a->mianownik)*(b->mianownik);
    b->licznik = nom;
    b->mianownik = denom;
}
Ulamek* div_frac(Ulamek* a, Ulamek* b)
{
    Ulamek* temp = create_fraction(b->mianownik, b->licznik);
    temp = mult(a, temp);
    return temp;
}

void _div(Ulamek* a, Ulamek* b)
{
    Ulamek* temp = create_fraction(b->mianownik, b->licznik);
    temp = mult(a, temp);
    b->licznik = temp->licznik;
    b->mianownik = temp->mianownik;
}

int main()
{
    Ulamek* a = create_fraction(5, 10);
    Ulamek* b = create_fraction(5, 15);
    print_fraction(a);
    print_fraction(b);
    Ulamek* c = add(a, b);
    print_fraction(c);
    c = sub(a, b);
    print_fraction(c);
    c = mult(a, b);
    print_fraction(c);
    c = div_frac(a, b);
    print_fraction(c);
    _mult(a, b);
    print_fraction(b);
}