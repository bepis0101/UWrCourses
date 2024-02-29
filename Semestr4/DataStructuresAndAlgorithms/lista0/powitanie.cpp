// Borys Adamiak
// 337295
// KPO

#include <bits/stdc++.h>

using namespace std;

void printNums(int a, int b) {
    const int MULT = 2024;
    int first = 0;
    int k = 0;
    while(first < a) {
        first = MULT * k;
        k++;
    }
    for(int i = first; i <= b; i += MULT) {
        cout << i << '\n';
    }
}

int main() {
    int a, b; cin >> a >> b;
    printNums(a, b);
    return 0;
}