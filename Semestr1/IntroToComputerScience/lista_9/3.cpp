// a) (n, 0, a)
// b) 
bool poprawne(int a[], int n)
{
    bool check = true;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j) continue;
            if(a[i] == a[j]) 
            {
                check = false;
                break;
            }
            if(a[i] == a[j]+abs(i-j) or a[i] == a[j]-abs(i-j))
            {
                check = false;
                break;
            }
        }
    }
    return check;
}
// c) funkcja hetmany sprawdza wiecej bo nie sprawdza na biezaco czy miejsce jest wolne