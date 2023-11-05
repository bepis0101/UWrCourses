#include <bits/stdc++.h>
using namespace std;

double x(double a, double x0) {
    double xn = x0;
    for(int i = 0; i < 10000; i++) {
        xn = xn/2.0 + a/(2.0*xn);
    }

    return xn;
}

int main() {
    for(double i = 0; i <= 12; i += 0.1) {
        cout << x(15, i) << endl;
    }
    for(double i = -1.0; i <= 100; i += 0.01) {
        cout << abs(x(11, i)) << '\n';
    }
}