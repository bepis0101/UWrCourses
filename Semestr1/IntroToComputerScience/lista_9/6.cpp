#include <bits/stdc++.h>

using namespace std;
const int N = 100;
int plansza[N+2][N+2];

int koszt[N+2][N+2];

int main()
{
    int n; cin >> n;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> plansza[i][j];
            koszt[i][j] = INT_MAX;
        }
    }
    koszt[0][0] = plansza[0][0];
    for(int i = 1; i < n; i++)
    {
        koszt[i][0] = koszt[i-1][0] + plansza[i][0];
        koszt[0][i] = koszt[0][i-1] + plansza[0][i];
    }
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < n; j++)
        {
            koszt[i][j] = plansza[i][j] + min(koszt[i-1][j], koszt[i][j-1]);
        }
    }
    cout << koszt[n-1][n-1];
}