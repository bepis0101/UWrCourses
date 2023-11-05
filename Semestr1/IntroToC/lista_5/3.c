#include <stdio.h>
#include <math.h>

long long min(long long a, long long b)
{
    if(a > b) return b;
    return a;
}
long long max(long long a, long long b)
{
    if(a > b) return a;
    return b;
}

int main()
{
    long long d; 
    long long x = scanf("%lld", &d);
    x = d*d;
    for(long long i = sqrt(d*d/3); i >= 1; i--)
    {
        for (long long j = sqrt((d*d-i*i)/2); j >= 1; j--)
        {
            
            long long pp = x-i*i-j*j;
            long long p = sqrt(x-i*i-j*j);
            if(pp == p*p && p > 0 && (p*p + i*i + j*j) == x)
            {
                long long w = p;
                long long mini = min(min(w, i), j);
                long long maks = max(max(w, i), j);
                long long mid;
                if(w != maks && w != mini)
                {
                    mid = w;
                }
                else if(i != maks && i != mini)
                {
                    mid = i;
                }
                else
                {
                    mid = j;
                }

                printf("%lld %lld %lld\n", maks, mid, mini);
                return 0;
            }
        }
        
    }
    printf("BRAK");
}