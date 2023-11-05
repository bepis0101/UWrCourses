#include <stdio.h>
int czy_trojkat(int a, int b, int c)
{
    if(a < b)
    {
        if(b < c)
        {
            if (a+b > c)
            {
                return 1;
            }
            return 0;
        }
        else
        {
            if (a+c > b)
            {
                return 1;
            }
            return 0;
        }
    }
    else
    {
        if(c < a)
        {
            if (c+b > a)
            {
                return 1;
            }
            return 0;
        }
        else
        if (b+a > c)
        {
            return 1;
        }
        return 0;
    }
}
int czy_prostokatny(int a, int b, int c)
{
    a = a*a;
    b = b*b;
    c = c*c;
    if(a > b)
    {
        if (a > c)
        {
            if(c+b == a)
            {
                return 1;
            }
            return 0;
        }
        else
        {
            if(a+b == c)
            {
                return 1;
            }
            return 0;
        }
    }
    else
    {
        if (b > c)
        {
            if(c+a == b)
            {
                return 1;
            }
            return 0;
        }
        else
        {
            if(a+b == c)
            {
                return 1;
            }
            return 0;
        }
    }
}
int przeciwprost (int a)
{
    for (int x = 2; x < a; x++)
    {
        for(int y = 2; y < a; y++)
        {
            if (y*y+x*x == a*a)
            {
                return 1;
            }
        }
    }
    return 0; 
}
int main()
{
    printf("Podaj trzy liczby naturalne wieksze od zera:\n" );
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("Twoje boki to a = %d, b = %d i c = %d\n", a, b, c);
    printf("Sprawdzimy czy z bokow o dlugosciach a, b, c mozna stworzyc trojkat:\n");
    if (czy_trojkat(a, b, c) == 1)
    {
        printf("Z bokow %d %d %d mozna stworzyc trojkat\n", a, b, c);
        printf("Sprawdzmy teraz czy jest to trojkat prostokatny:\n");
        if(czy_prostokatny(a, b, c ) == 1)
        {
            printf("Trojkat o podanych bokach jest prostokatny\n");
        }
        else
        {
            printf("Podane boki nie tworza trojkta prostokatnego\n");
        }
    }
    else
    {
        printf("Twoje boki nie moga stworzyc trojkata\n");
    }

    printf("Sprawdzmy teraz czy na przeciwprostokatnej %d da sie zbudowac trojkat prostokatny o bokach dlugosci calkowitej\n", a);
    if (przeciwprost(a) == 1)
    {
        printf("Jest to mozliwe\n");
    }
    else
    {
        printf("Nie jest to mozliwe\n");
    }

    return 0;

}
