#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 20;

vector<int> tree[N];
int up[N][LOG];
int depth[N];
int cnt[N];
int res[N];

void dfs(int u, int p) {
  up[u][0] = p;
  for (int v : tree[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }
}

void dfs_sum(int u, int p) {
  for (int v : tree[u]) {
    if (v != p) {
      dfs_sum(v, u);
      cnt[u] += cnt[v];
    }
  }
  res[u] = cnt[u];
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];
  for (int i = 0; i < LOG; i++) {
    if (diff & (1 << i))
      u = up[u][i];
  }

  if (u == v)
    return u;

  for (int i = LOG-1; i >= 0; i--) {
    if (up[u][i] != 0 && up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  }
  return up[u][0];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dfs(1, 0);

  // Preprocessing
  for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      if (up[i][j-1] != 0)
        up[i][j] = up[up[i][j-1]][j-1];
    }
  }

  // Przetwarzanie ścieżek
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    cnt[u]++;
    cnt[v]++;
    int ancestor = lca(u, v);
    cnt[ancestor]--;
    if (up[ancestor][0] != 0) cnt[up[ancestor][0]]--;
}


  // DFS sumujący liczniki
  dfs_sum(1, 0);

  for (int i = 1; i <= n; i++) {
    cout << res[i] << ' ';
  }
  cout << '\n';
}
