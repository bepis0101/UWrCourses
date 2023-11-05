#include <bits/stdc++.h>
using namespace std;
double f(double x) {
    return 2023.0*(1.0-(289.0/12.0)*x*x);
}
int main() {
    for(int i = 11; i <= 20; i++) { 
        double x = 1.0/pow(10, i);
        cout << "x = " << x << ", f(x) = " << f(x) << '\n';
    }
}