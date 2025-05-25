#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+3;

int up[N][20];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, q; cin >> n >> q;
  for(int i = 2; i <= n; i++) {
    cin >> up[i][0];
  }
  // root
  up[1][0] = 0;
  for(int i = 1; i < 20; i++) {
    for(int j = 1; j <= n; j++) {
      if(up[j][i-1] != 0) {
        up[j][i] = up[up[j][i-1]][i-1];
      } else {
        up[j][i] = 0;
      }
    }
  }
  while(q--) {
    int v, k; cin >> v >> k;
    for(int i = 0; i < 20; i++) {
      if(k & (1 << i)) {
        v = up[v][i];
        if(v == 0) break; // szukany wierzchołek nie istnieje
      }
    }
    cout << (v == 0 ? -1 : v) << '\n';
  }
}