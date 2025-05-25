#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+3;
vector<long long> tree;
vector<int> graph[N];
vector<long long> input;
int pre[N], post[N];
int timer;

long long flat[N];

void dfs(int u, int p) {
  pre[u] = timer;
  flat[timer] = input[u];
  timer++;
  for(int v : graph[u]) {
    if(v != p) {
      dfs(v, u);
    }
  }
  post[u] = timer-1;
}

void build(int node, int tl, int tr) {
  if(tl == tr) {
    tree[node] = flat[tl];
  } else {
    int tm = (tl+tr) / 2;
    build(2*node, tl, tm);
    build(2*node+1, tm+1, tr);
    tree[node] = tree[2*node] + tree[2*node+1];
  }
}

void update(int node, int tl, int tr, int pos, long long val) {
  if(tl == tr) {
    tree[node] = val;
  } else {
    int tm = (tl + tr) / 2;
    if(pos <= tm) update(2*node, tl, tm, pos, val);
    else update(2*node+1, tm+1, tr, pos, val);
    tree[node] = tree[2*node]+tree[2*node+1];
  }
}

long long query(int node, int tl, int tr, int ql, int qr) {
  if(ql > qr) return 0;
  if(ql == tl && qr == tr) {
    return tree[node];
  }
  int tm = (tl+tr) / 2;
  return query(2*node, tl, tm, ql, min(qr, tm)) +
         query(2*node+1, tm+1, tr, max(ql, tm+1), qr);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, q; cin >> n >> q;
  tree.resize(4*n);
  input.resize(n);

  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  for(int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs(0, -1);
  build(1, 0, n-1);

  while(q--) {
    int flag; cin >> flag;
    int v;
    switch(flag) {
      case 1:
        long long x; cin >> v >> x;
        v--;
        update(1, 0, n-1, pre[v], x);
        break;
      case 2:
        cin >> v;
        v--;
        cout << query(1, 0, n-1, pre[v], post[v]) << '\n';
        break;
    }
  }
  return 0;
}