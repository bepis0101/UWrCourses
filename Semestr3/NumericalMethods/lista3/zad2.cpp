#include <bits/stdc++.h>

using namespace std;

pair<double, double> solve(double a, double b, double c) {
    if(b*b - 4*a*c < 0) throw invalid_argument("Delta < 0");
    double x1, x2;
    x1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
    x2 = (-b - sqrt(b*b - 4*a*c))/(2*a);
    return {x1, x2};
}

pair<double, double> solveBetter(double a, double b, double c) {
    if(b*b - 4*a*c < 0) throw invalid_argument("Delta < 0");
    double x1, x2;
    if(b >= 0) {
        x1 = -2.0*c/(sqrt(b*b - 4*a*c)+b);
        x2 = c/(a*x1);    
    } else { 
        x1 = -2.0*c/(b-sqrt(b*b - 4*a*c));
        x2 = c/(a*x1);
    }
    return {x1, x2};
}

int main() {
    double a, b, c;
    a = 0.0001, b = 134234, c = 0.111;
    try {
        auto [x1, x2] = solve(a, b, c);
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    } catch(invalid_argument& e) {
        cout << e.what() << endl;
    }
    try {
        auto [x1, x2] = solveBetter(a, b, c);
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    } catch(invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}