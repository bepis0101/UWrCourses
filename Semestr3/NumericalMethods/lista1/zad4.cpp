#include <bits/stdc++.h>
using namespace std;

double rec(int n) {
    if(n == 0) return 1;
    if(n == 1) return (double)-1.0/9.0;
    else {
        return (double)80.0*rec(n-1)/9.0+rec(n-2);
    }
}

double geo(int n) {
    return pow((-1.0/9.0), n);
}

int main() {

    for(int i = 2; i <= 50; i++) {
        cout << geo(i) << '\n';
    }
}

