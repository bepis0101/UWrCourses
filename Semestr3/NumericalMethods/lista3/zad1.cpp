#include <bits/stdc++.h>

using namespace std;

double f_fixed(double x) {
    return (sqrt(pow(x, 6.0) + 4092529.0) - pow(x, 3.0))/4092529.0;
}

double g_fixed(double x) {
    return log2(x/4.0);
}

double h_fixed(double x) {
    return atan(x)/pow(x, 3.0) - 1.0/x*x;
}

double h(double x) {
    double arccot = M_PI_2-atan(x);
    return (M_PI_2-x-arccot)/pow(x, 3.0);
}

int main() {
    cout << f_fixed(-100000) << '\n';
    double x = 4.000000000000001;
    cout << log2(x) - 2.0 << '\n';
    cout << g_fixed(x) << '\n';
    x = 0.00001;
    cout << h(x) << '\n' << h_fixed(x);
}