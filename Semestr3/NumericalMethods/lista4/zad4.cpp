#include <bits/stdc++.h>
using namespace std;

double f(double x) {
    return pow(x, 4.0) - log(x + 4.0);
}

double bisect(double a, double b, double eps) {
    double x = (a+b)/2.0;
    if(abs(f(x)) < eps) {
        return x;
    }
    
    if(f(a)*f(x) > 0) {
        return bisect(x, b, eps);
    } else {
        return bisect(a, x, eps);
    }

}

int main() {
    cout << bisect(0.0, 2.0, 1e-8) << '\n' << bisect(-1.3, -1.0, 1e-8) << '\n';
    return 0;
}