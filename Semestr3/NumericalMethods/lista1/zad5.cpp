#include <bits/stdc++.h>
using namespace std;

double tab[21];


int main() {
    tab[0] = log(2024.0/2023.0);
    for(int i = 1; i <= 21; i++) {
        tab[i] = 1.0/double(i) - 2023.0*tab[i-1];
    }

    for(int i = 0; i <= 21; i++) {
        cout << tab[i] << '\n';
    }
    

}
