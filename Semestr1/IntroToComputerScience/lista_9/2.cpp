#include <bits/stdc++.h>

using namespace std;
#define n 6 //rozmiar szachownicy
int b[n];
void init()
{int i;
for (i=0; i<n; i++) b[i]=-1;
}
int isfree(int x, int y)
{int i;
for (i=0; i<x; i++)
if (b[i]-i==y-x || b[i]+i==y+x ||
b[i]==y) return 0;
return 1;
}
int queens()
// algorytm z nawrotami
// queens() = n gdy znalezione rozwiązanie
// queens() = -1 gdy brak rozwiązania
{ 
    int k, suma = 0;
    for (int i = 0; i < n; i++)
    {
        b[0]= i; // umieść pierwszego hetmana w „lewym dolnym” narożniku (na dole kolumny 0)
        k=1; // przejdź do kolumny numer 1
        while (k<n && k>=0)
        { do //poszukiwanie „wolnego” pola w kolumnie k, idąc w górę od b[k]
        { b[k]++; }
        while (b[k]<n && !isfree(k,b[k]));
        if (b[k]<n) k++; //wolne pole znalezione, przejście do nast. kolumny!!!
        else {b[k]=-1; k--;} //brak wolnego pola, powrót do poprzedniej kolumny!
        }
        if(k == n) suma++;
    }
    return suma;
}

int main()
{
    cout << queens();
}