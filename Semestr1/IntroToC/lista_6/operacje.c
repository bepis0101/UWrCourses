int palindrom(char *string)
{
    char *x = string;
    while(*x != '\0')
    {
        x++;
    }
    x--;
    char *begin = string;
    while(begin < x)
    {
        if (*x != *begin)
        {
            return 0;
        }
        begin++;
        x--;
    }
    return 1;
}
void reverse(char *t)
{
    char *x = t;
    while(*x != '\0')
    {
        x++;
    }
    x--;
    while(x >= t)
    {
        putchar(*x);
        x--;
    }
}