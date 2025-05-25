#include <bits/stdc++.h>

using namespace std;

vector<int> input;
vector<int> tree;

void build(int l, int r, int node) {
  if(l == r) tree[node] = input[l];
  else {
    int mid = (l+r) / 2;
    build(l, mid, 2*node);
    build(mid+1, r, 2*node+1);
    tree[node] = max(tree[2*node], tree[2*node+1]);
  }
}

void update(int l, int r, int node, int val, int idx) {
  if(l == r) tree[node] = val;
  else {
    int mid = (l+r) / 2;
    if(idx <= mid) {
      update(l, mid, 2*node, val, idx);
    } else {
      update(mid+1, r, 2*node+1, val, idx);
    }
    tree[node] = max(tree[2*node], tree[2*node+1]);
  }
}

int query(int l, int r, int node, int k) {
  if(tree[node] < k) {
    return -1;
  }
  if(l == r) {
    return l;
  }
  int mid = (l+r) / 2;
  if(tree[2*node] >= k) {
    return query(l, mid, 2*node, k);
  } else {
    return query(mid+1, r, 2*node+1, k);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, q; cin >> n >> q;
  input.resize(n);
  tree.resize(4*n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  build(0, n-1, 1);
  for(int i = 0; i < q; i++) {
    int k; cin >> k;
    int idx = query(0, n-1, 1, k);
    if(idx == -1) {
      cout << 0 << ' ';
    } else {
      input[idx] -= k;
      update(0, n-1, 1, input[idx], idx);
      cout << (idx+1) << ' ';
    }
  }
}