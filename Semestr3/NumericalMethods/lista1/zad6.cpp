#include <bits/stdc++.h>
using namespace std;

double func(int n) {
    double sum = 0.0;
    for(int i = 0; i <= n; i++) {
        if(i%2 == 0) {
            sum += 1.0/(2.0*i + 1.0);
        } else {
            sum -= 1.0/(2.0*i + 1.0);
        }
    }
    return sum*4.0;
}


int main() {
    cout << setprecision(9) << func(2000000) << "\n";
}