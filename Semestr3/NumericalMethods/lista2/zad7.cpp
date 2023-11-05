#include <bits/stdc++.h>
using namespace std;

double f(double x) {
    return 4046.0/(1.0 + sqrt(pow(x, 14.0) + 1));
}

int main() {
    double x = 0.001;
    cout << f(x) << '\n';
}