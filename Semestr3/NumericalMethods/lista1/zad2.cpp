#include <bits/stdc++.h>
using namespace std;

double power(double x, int n) {
    double res = 1.0;
    for(int i = 0; i < n; i++) {
        res *= x;
    }
    return res;
}

double f(double x) {
    return 4046*(sqrt(power(x, 14) + 1)-1)/power(x, 14);
}

int main() {
    double x = 0.001;
    cout << f(x) << "\n"; 
}