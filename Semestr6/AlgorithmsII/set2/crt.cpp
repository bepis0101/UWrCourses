#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+3;

long long A[N], P[N];

// gcd(a, b) = ax + by

// extended euclidean algorithm O(log a) time complexity
pair<long long, long long> extended_euclidean(long long a, long long b) {
  if(b == 0) return {1, 0};
  auto p = extended_euclidean(b, a%b);
  return {p.second, p.first - (a/b * p.second)};
}

long long modular_inverse(long long a, long long mod) {
  auto p = extended_euclidean(a, mod);
  return (p.first % mod + mod) % mod;
}



int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  while(n--) {
    int k; cin >> k;
    long long mod = 1;
    for(int i = 0; i < k; i++) {
      cin >> P[i] >> A[i];
      mod *= P[i];
    }
    long long res = 0;
    for(int i = 0; i < k; i++) {
      long long Mi = mod / P[i];
      long long inv = modular_inverse(Mi, P[i]);
      res = (res + A[i] * Mi * inv) % mod;
    }
    cout << res << '\n';
  }
}