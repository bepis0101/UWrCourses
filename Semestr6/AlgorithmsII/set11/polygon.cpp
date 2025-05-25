#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
long long xs[N], ys[N];

// funkcja do wypisania __int128
void print128(__int128 x) {
  if (x == 0) {
    cout << "0";
    return;
  }
  string s;
  while (x > 0) {
    s += '0' + x % 10;
    x /= 10;
  }
  reverse(s.begin(), s.end());
  cout << s;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> xs[i] >> ys[i];
  }
  xs[n] = xs[0];
  ys[n] = ys[0];

  __int128 sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (__int128)xs[i] * ys[i+1] - (__int128)xs[i+1] * ys[i];
  }
  if(sum < 0) {
    sum = -sum; 
  }

  if(sum % 2 == 0) {
    print128(sum / 2);
    cout << ".0\n";
  } else {
    print128(sum / 2);
    cout << ".5\n";
  }
}
