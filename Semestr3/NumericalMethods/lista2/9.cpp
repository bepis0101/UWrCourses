#include <bits/stdc++.h>
using namespace std;

double x[1000001];


void init() {
    x[1] = 2.0;
    for (int i = 1.0; i <= 1000000; i++) {
        x[i+1] = sqrt(2.0*pow(x[i], 2.0) / (1.0 + sqrt(1.0 - pow(x[i], 2.0)/pow(4.0, i))));
    }
}

int main() {
    init();
    cout << x[15] << '\n';
}