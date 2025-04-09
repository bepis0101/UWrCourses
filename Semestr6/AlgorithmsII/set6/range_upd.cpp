#include <bits/stdc++.h>


using namespace std;
vector<int> input;
vector<long long> tree;
vector<long long> lazy;

void build(const vector<int>& a, int v, int l, int r) {
  if (l == r) {
    tree[v] = a[l];
  } else {
    int mid = (l + r) / 2;
    build(a, 2 * v, l, mid);
    build(a, 2 * v + 1, mid + 1, r);
    tree[v] = 0; // nieporzebne, bo tylko punktowe zapytania
  }
}

void push(int v, int l, int r) {
  if (lazy[v] != 0) {
    tree[v] += lazy[v]; // dodajemy do węzła
    if (l != r) {
      lazy[2 * v] += lazy[v];
      lazy[2 * v + 1] += lazy[v];
    }
    lazy[v] = 0;
  }
}

void range_add(int v, int l, int r, int lo, int hi, long long addend) {
  push(v, l, r);
  if (lo > hi) return;
  if (lo == l && hi == r) {
    lazy[v] += addend;
    push(v, l, r);
  } else {
    int mid = (l + r) / 2;
    range_add(2 * v, l, mid, lo, min(hi, mid), addend);
    range_add(2 * v + 1, mid + 1, r, max(lo, mid + 1), hi, addend);
  }
}

long long point_query(int v, int l, int r, int pos) {
  push(v, l, r);
  if (l == r) {
    return tree[v];
  }
  int mid = (l + r) / 2;
  if (pos <= mid)
    return point_query(2 * v, l, mid, pos);
  else
    return point_query(2 * v + 1, mid + 1, r, pos);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; cin >> n >> q;
  input.resize(n);
  tree.resize(4*n);
  lazy.resize(4*n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  build(input, 1, 0, n-1);
  while(q--) {
    int flag; cin >> flag;
    switch(flag) {
      case 1:
        int x, y, v; cin >> x >> y >> v;
        range_add(1, 0, n-1, x-1, y-1, v);
        break;
      case 2:
        int k; cin >> k;
        cout << point_query(1, 0, n-1, k-1) << '\n';
        break;
    }
  }
  return 0;
}