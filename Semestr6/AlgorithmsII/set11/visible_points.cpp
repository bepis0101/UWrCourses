#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q; cin >> q;
  int n; cin >> n;
  map<pair<int, int>, int> slopes;
  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    int nom = y, denom = x-q;
    x = nom/gcd(nom, denom);
    y = denom/gcd(nom, denom);
    slopes[{x, y}]++;
  }
  cout << slopes.size();
}