//Borys Adamiak zadanie 1 lista 7 
// :)))

#include <stdio.h>
#define and &&
#define or ||

int zamiana_czasu(int sek, int min, int hr)
{
    return sek + 60*min + 3600*hr;
}

void write(int x)
{
    int hr = x/3600;
    int min = (x-hr*3600)/60;
    int sek = x - 60*min - 3600*hr;
    if (hr > 0) printf("%d:%02d:%02d\n", hr, min, sek);
    else if(min > 0) printf("%d:%02d\n", min, sek);
    else printf("%d\n", sek);
}
void mult(int x)
{
    int a; 
    scanf("%d", &a);
    write(x*a);
}
void div(int x)
{
    int a; 
    scanf("%d", &a);
    write(x/a);
}
void add(int a, int b)
{
    write(a+b);
}
void sub(int a, int b)
{
    write(a-b);
}

int main()
{
    int sek = 0;
    int min = 0;
    int hr = 0;

    scanf("%d", &sek);
    while(sek != 0 && !feof(stdin))
    {
        char nic;
        scanf("%c", &nic);
        if(nic == ':')
        {
            min = sek;
            scanf("%d", &sek);
            //printf("%d %d ", sek, min);
            scanf("%c", &nic);
            if(nic == ':')
            {
                hr = min;
                min = sek;
                scanf("%d", &sek);
                //printf("%d %d %d", sek, min, hr);
            }
        }
        while (nic != '+' && nic != '-' && nic != '*' && nic != '/')
        {
            scanf("%c", &nic);
        }
        int t1 = zamiana_czasu(sek, min, hr);
        sek = 0; min = 0; hr = 0;
        if(nic == '*')
        {
            mult(t1);
        }
        else if(nic == '/')
        {
            div(t1);
        }
        else
        {
            char znak = nic;
            scanf("%d", &sek);
            scanf("%c", &nic);
            if(nic == ':')
            {
                min = sek;
                scanf("%d", &sek);
                scanf("%c", &nic);
                if(nic == ':')
                {
                    hr = min;
                    min = sek;
                    scanf("%d", &sek);
                }
            }
            int t2 = zamiana_czasu(sek, min, hr);
            if(znak == '+')
            {
                add(t1, t2);
            }
            if (znak == '-')
            {
                sub(t1, t2);
            }
        }

        scanf("%d", &sek);

    }
}