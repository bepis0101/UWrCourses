#include <bits/stdc++.h>
using namespace std;

float fsingle(float x) {
    return 14.0*(1-cos(17.0*x))/x*x;
}

double fdouble(double x) {
    return 14.0*(1-cos(17.0*x))/x*x;
}


int main() {
    
    float x = 0.00000000001;
    double y = 0.00000000001;
    for(int i = 1; i < 11; i++) {
        cout << fsingle(x) << '\n';
        cout << fdouble(y) << '\n';
        x /= 10.0;
        y /= 10.0;
    }
    return 0;
}

// wyniki nie sa poprawne poniewaz nie wazne jak niski bedzie x, nie dotrze on nigdy do 0 (cos(0) = 1)
// wiec 1-cos(17x) zawsze bedzie wieksze od 0 wiec nie bedzie wyniku 0
