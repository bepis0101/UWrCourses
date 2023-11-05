#include <stdio.h>

int max(int x, int y )
{
    if(x > y) return x;
    return y;
}

int main()
{
	int n, w, suma=0, ac;
	scanf("%d", &n);
	int ciag[n];
	for(int a = 0; a < n; a++)
	{
		scanf("%d", &ciag[a]);
	}
	for(int i = 0; i < n; i++)
	{
		w = ciag[i];
		ciag[i] = -1;
		if(w != -1){
			int s = 1;
			while(w != i+1)
			{
				ac = w;
				w = ciag[w-1];
				ciag[ac-1] = -1;
				s++;
			}
			suma = max(s,suma);
		}
	}
	printf("%d", suma);

	return 0;
}

