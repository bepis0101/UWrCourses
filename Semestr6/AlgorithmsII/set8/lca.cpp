#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+3;

int up[N][20];
int depth[N];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, q; cin >> n >> q;
  for(int i = 2; i <= n; i++) {
    int p; cin >> p;
    up[i][0] = p;
    depth[i] = depth[p]+1;
  }
  // root
  up[1][0] = 0;
  for(int i = 1; i < 20; i++) {
    for(int j = 1; j <= n; j++) {
      if(up[j][i-1] != 0) {
        up[j][i] = up[up[j][i-1]][i-1];
      }
    }
  }
  while(q--) {
    int u, v; cin >> u >> v;
    if(depth[v] > depth[u]) swap(u, v);
    int diff = depth[u]-depth[v];
    for(int i = 0; i < 20; i++) {
      if(diff & (1 << i)) {
        u = up[u][i];
      }
    }
    if(u == v) {
      cout << u << '\n';
      continue;
    }
    for(int i = 19; i >= 0; i--) {
      if(up[u][i] != 0 && up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];    
      }
    }
    cout << up[u][0] << '\n';
  }
}