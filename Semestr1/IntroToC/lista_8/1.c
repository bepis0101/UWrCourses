#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>

typedef struct zespolone
{
    float rzeczywista; // czesc rzeczywista 
    float urojona; // czesc urojona
}zespolone;
zespolone dodawanie(zespolone a, zespolone b)
{
    zespolone c;
    c.rzeczywista = a.rzeczywista + b.rzeczywista;
    c.urojona = a.urojona + b.urojona;
    return c;
}
zespolone odejmowanie(zespolone a, zespolone b)
{
    zespolone c;
    c.rzeczywista = a.rzeczywista - b.rzeczywista;
    c.urojona = a.urojona - b.urojona;
    return c;
}
zespolone mnozenie(zespolone a, zespolone b)
{
    zespolone c;
    c.rzeczywista = a.rzeczywista*b.rzeczywista - a.urojona*b.urojona;
    c.urojona = a.rzeczywista*b.urojona + a.urojona*b.rzeczywista;
    return c;
}
zespolone iteracje(zespolone z, zespolone c)
{
    for(int h = 0; h < 200; h++)
    {
        z = odejmowanie(mnozenie(z, z), c);
    }
    return z;
}

int main(int argc, char *argv[])
{
    zespolone c;
    int x, y;
    if(argc == 1)
    {
        c.rzeczywista = 0.2;
        c.urojona = 0.75;
        x = 40; y = 25;
    }
    if(argc > 2)
    {
        x = atoi(argv[1]); y = atoi(argv[2]);
        c.rzeczywista = 0.2;
        c.urojona = 0.75;
    }
    if (argc > 4)
    {
        c.rzeczywista = atof(argv[3]); c.urojona = atof(argv[4]);
    }
    // printf("%d %d %f %f\n", x, y, c.rzeczywista, c.urojona);
    float ox = 2.0/x, oy = 2.0/y;
    for(float i = 1; i >= -1; i -= oy)
    {
        for(float j = 1; j >= -1; j -= ox)
        {
            zespolone z;
            z.rzeczywista = j;
            z.urojona = i;
            z = iteracje(z, c);
            if(z.rzeczywista*z.rzeczywista + z.urojona*z.urojona < 4)
            {
                putchar('0');
            }
            else
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }

}