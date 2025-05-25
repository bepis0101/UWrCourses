#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4e5+2;
vector<int> tree[MAXN];
int depth[MAXN];
int first[MAXN];
vector<int> euler;
int seg[4 * MAXN];

void dfs(int v, int p, int d) {
  depth[v] = d;
  first[v] = euler.size();
  euler.push_back(v);
  for (int u : tree[v]) {
    if (u != p) {
      dfs(u, v, d + 1);
      euler.push_back(v);
    }
  }
}

void build(int node, int l, int r) {
  if (l == r) {
    seg[node] = euler[l];
  } else {
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    int left = seg[2 * node];
    int right = seg[2 * node + 1];
    seg[node] = (depth[left] < depth[right] ? left : right);
  }
}

int query(int node, int l, int r, int ql, int qr) {
  if (qr < l || r < ql)
    return -1;
  if (ql <= l && r <= qr)
    return seg[node];
  int mid = (l + r) / 2;
  int left = query(2 * node, l, mid, ql, qr);
  int right = query(2 * node + 1, mid + 1, r, ql, qr);
  if (left == -1) return right;
  if (right == -1) return left;
  return (depth[left] < depth[right] ? left : right);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dfs(1, -1, 0);
  build(1, 0, euler.size() - 1);

  while (q--) {
    int u, v;
    cin >> u >> v;
    int l = first[u];
    int r = first[v];
    if (l > r) swap(l, r);
    int lca = query(1, 0, euler.size() - 1, l, r);
    int dist = depth[u] + depth[v] - 2 * depth[lca];
    cout << dist << '\n';
  }

  return 0;
}
