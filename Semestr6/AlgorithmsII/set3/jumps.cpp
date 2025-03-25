#include <bits/stdc++.h>
using namespace std;

#define cerr if(0) cout

const int N = 2e5 + 4;
const int B = 450;

int input[N];
long long precalc_sum[N][B];

void preproccess(int n) {
  int maks = ceil(sqrt(n));
  for(int b = 1; b <= maks; b++) {
    for(int a = n; a >= 1; a--) {
      if(a + b <= n) {
        precalc_sum[a][b] = input[a] + precalc_sum[a+b][b];
      } else {
        precalc_sum[a][b] = input[a];
      }
    }
  }
}

long long query(int a, int b, int n) {
  if(b <= ceil(sqrt(n))) {
    cerr << "small dif: ";
    return precalc_sum[a][b];
  } else {
    long long res = 0;
    for(int i = a; i <= n; i += b) {
      res += input[i];
    }
    cerr << "big diff: ";
    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> input[i];
  }

  preproccess(n);

  int q; cin >> q;
  while(q--) {
    int a, b; cin >> a >> b;
    cout << query(a, b, n) << '\n';
  }
}