#include <bits/stdc++.h>

using namespace std;

vector<int> tree;
vector<int> lazy;

void build(int val, int l, int r, int node) {
  if(l == r) {
    tree[node] = val;
  } else {
    int mid = (l+r) / 2;
    build(val, l, mid, 2*node);
    build(val, mid+1, r, 2*node+1);
    tree[node] = min(tree[2*node], tree[2*node+1]);
  }
}

void push(int l, int r, int node) {
  if(lazy[node] != 0) {
    tree[node] -= lazy[node];
    if(l != r) {
      lazy[2*node] += lazy[node];
      lazy[2*node+1] += lazy[node];
    }
    lazy[node] = 0;
  }
}

int query(int l, int r, int node, int tl, int tr) {
  push(tl, tr, node);
  if(l > tr || r < tl) return INT_MAX;
  if(l <= tl && r >= tr) return tree[node];
  int tmid = (tr+tl) / 2;
  return min(query(l, r, 2*node, tl, tmid), 
             query(l, r, 2*node+1, tmid+1, tr));
}

void update(int l, int r, int node, int val, int tl, int tr) {
  push(tl, tr, node);
  if(l > tr || r < tl) return;
  if(l <= tl && r >= tr) {
    lazy[node] += val;
    push(tl, tr, node);
    return;
  }
  int tmid = (tl+tr) / 2;
  update(l, r, 2*node, val, tl, tmid);
  update(l, r, 2*node+1, val, tmid+1, tr);
  tree[node] = min(tree[2*node], tree[2*node+1]);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m, q; cin >> n >> m >> q;
  tree.resize(4*n);
  lazy.resize(4*n);
  build(m, 0, n-1, 1);
  for(int i = 0; i < q; i++) {
    int p, k, l; cin >> p >> k >> l;
    // jezeli mamy wiecej wolnych miejsc na danym przedziale niz potrzebujemy
    if(query(p-1, k-2, 1, 0, n-1) >= l) {
      update(p-1, k-2, 1, l, 0, n-1);
      cout << "T\n";
    } else {
      cout << "N\n";
    }
  }
}