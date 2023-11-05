#include <bits/stdc++.h>
using namespace std;

double x(double a, double x0) {
    double xn = x0;
    int num_of_iterations = 0;
    while(true) {
        double xn1 = 0.5*(3*xn - a*xn*xn*xn);
        num_of_iterations++;
        if(abs(xn1 - xn) < 1e-6) {
            return num_of_iterations;
        }
        xn = xn1;
    }
}

int main() {
    int numOfTests = 0;
    int sumOfIterations = 0;
    for(double i = 0.1; i <= 1.0; i += 0.1) {
        sumOfIterations += x(2.0, i);
        numOfTests++;
    }
    cout << "Average number of iterations: " << sumOfIterations/numOfTests << '\n';
}