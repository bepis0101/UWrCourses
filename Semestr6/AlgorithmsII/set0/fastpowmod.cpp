#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9;

int power(long long a, long long n) {
  long long res = 1;

  while(n > 0) {
    if(n % 2 == 1) {
      res = (res  * a) % mod;
    }
    a = (a*a) % mod;
    n /= 2;
  }
  return res;
}

int main() {
  long long a; long long n; cin >> a >> n;
  cout << power(a, n);
}