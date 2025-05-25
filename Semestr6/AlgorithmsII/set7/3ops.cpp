#include <bits/stdc++.h>

using namespace std;

vector<long long> input;
vector<long long> tree;
vector<long long> lazyAdd;
vector<long long> lazySet;
vector<bool> toSet;

void build(int l, int r, int node) {
  if(l == r) {
    tree[node] = input[l];
  } else {
    int mid = (l+r) / 2;
    build(l, mid, 2*node);
    build(mid+1, r, 2*node+1);
    tree[node] = tree[2*node] + tree[2*node+1];
  }
}

void push(int node, int l, int r) {
  if(toSet[node]) {
    tree[node] = lazySet[node] * (r-l+1);
    if(l != r) {
      toSet[2*node] = toSet[2*node+1] = true;
      lazySet[2*node] = lazySet[2*node+1] = lazySet[node];
      lazyAdd[2*node] = lazyAdd[2*node+1] = 0;
    }
    toSet[node] = false;
    lazySet[node] = 0;
  }

  if(lazyAdd[node] != 0) {
    tree[node] += lazyAdd[node] * (r-l+1);
    if(l != r) {
      lazyAdd[2*node] += lazyAdd[node];
      lazyAdd[2*node+1] += lazyAdd[node];
    }
    lazyAdd[node] = 0;
  }
}

void updateAdd(int ql, int qr, int node, int val, int l, int r) {
  push(node, l, r);
  if(ql > r || qr < l) return;
  if(ql <= l && qr >= r) {
    lazyAdd[node] += val;
    push(node, l, r);
    return;
  }
  int mid = (l+r) / 2;
  updateAdd(ql, qr, 2*node, val, l, mid);
  updateAdd(ql, qr, 2*node+1, val, mid+1, r);
  tree[node] = tree[2*node] + tree[2*node+1];
}

void updateSet(int ql, int qr, int node, int val, int l, int r) {
  push(node, l, r);
  if(ql > r || qr < l) return;
  if(ql <= l && qr >= r) {
    toSet[node] = true;
    lazySet[node] = val;
    lazyAdd[node] = 0;
    push(node, l, r);
    return;
  }

  int mid = (l+r) / 2;
  updateSet(ql, qr, 2*node, val, l, mid);
  updateSet(ql, qr, 2*node+1, val, mid+1, r);
  tree[node] = tree[2*node] + tree[2*node+1];
}

long long query(int ql, int qr, int node, int l, int r) {
  push(node, l, r);
  if(qr < l || ql > r) return 0;
  if(ql <= l && r <= qr) return tree[node];
  int mid = (l+r) / 2;
  return query(ql, qr, 2*node, l, mid) + query(ql, qr, 2*node+1, mid+1, r);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, q; cin >> n >> q;
  input.resize(n);
  tree.resize(4*n);
  lazyAdd.resize(4*n);
  lazySet.resize(4*n);
  toSet.resize(4*n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  build(0, n-1, 1);
  for(int i = 0; i < q; i++) {
    int type; cin >> type;
    int x, y, v;
    switch(type) {
      case 1:
        cin >> x >> y >> v;
        updateAdd(x-1, y-1, 1, v, 0, n-1);
        break;
      case 2:
        cin >> x >> y >> v;
        updateSet(x-1, y-1, 1, v, 0, n-1);
        break;
      case 3:
        cin >> x >> y;
        cout << query(x-1, y-1, 1, 0, n-1) << '\n';
        break;
      default: break;
    }
  }
  return 0;
}