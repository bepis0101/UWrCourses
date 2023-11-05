#include <stdio.h>
long long day(long long suma_szyszek, int w, int h, int field[101][101])
{
    for (int y = 0; y < h; y++)
    {
        int x = w-1;
        while(x >= 0)
        {
            if(field[y][x] == 9)
            {
                suma_szyszek++;
                x -= 10;
            }
            else
            {
                int x1 = x;
                x -= (field[y][x]+1);
                if(field[y][x1] != 0) field[y][x1]++;
            }
        }
    }
    return suma_szyszek;
}
long long noon(long long suma_szyszek, int w, int h, int field[101][101])
{
    for (int x = 0; x < w; x++)
    {
        int y = h-1;
        while(y >= 0)
        {
            if(field[y][x] == 9)
            {
                suma_szyszek++;
                y-=10;
            }
            else
            {
                int y1 = y;
                y -= (field[y][x]+1);
                if(field[y1][x] != 0) field[y1][x]++;
            }
        }
    }
    return suma_szyszek;
}
long long eve(long long suma_szyszek, int w, int h, int field[101][101])
{
    for (int y = 0; y < h; y++)
    {
        int x = 0;
        while(x < w)
        {
            if(field[y][x] == 9)
            {
                suma_szyszek++;
                x += 10;
            }
            else
            {
                int x1 = x;
                x += (field[y][x]+1);
                if(field[y][x1] != 0) field[y][x1]++;
            }
        }
    }
    return suma_szyszek;
}


int main()
{
    int w, h;
    scanf("%d%d", &w, &h);
    int field[101][101] = {0};
    long long d;
    scanf("%lld", &d);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            char c;
            if (scanf(" %c", &c) != 1) return 1;// Wczytuje kolejny niebiały znak
            if (c >= '1' && c <= '9') 
            {
                field[i][j] = (c - '0');
            }
        }
    }
    long long suma_szyszek = 0;
    for (long long i = 0; i < d; i++)
    {
        suma_szyszek = day(suma_szyszek, w, h, field);
        suma_szyszek = noon(suma_szyszek, w, h, field);
        suma_szyszek = eve(suma_szyszek, w, h, field);
    }
    printf("%lld\n", suma_szyszek);

}