#include <bits/stdc++.h>

using namespace std;

vector<double> res;

double f(double x) {
    return x-0.49;
}



void bisekcja(double a, double b) {
    for(int i = 0; i < 5; i++) {
        double x = (a+b)/2.0;
        res.push_back(x);
        if(f(x) > 0) {
            b = x;
        } else {
            a = x;
        }
    }
}

int main() {
    bisekcja(0.0, 1.0);
    for(int i = 0; i < 5; i++) {
        cout << abs(0.49-res[i]) << ' ' << 1.0/pow(2.0, i+1) << '\n';
    }
    return 0; 

}