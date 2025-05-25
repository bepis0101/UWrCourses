#include <bits/stdc++.h>

using namespace std;

vector<int> input;
vector<int> tree;
vector<int> deletes;

void build(int l, int r, int node) {
  if(l == r) tree[node] = 1;
  else {
    int mid = (l+r) / 2;
    build(l, mid, 2*node);
    build(mid+1, r, 2*node+1);
    tree[node] = tree[2*node] + tree[2*node+1];
  }
}

void remove(int l, int r, int node, int idx) {
  if(l == r) tree[node] = 0;
  else {
    int mid = (l+r) / 2;
    if(idx <= mid) {
      remove(l, mid, 2*node, idx);
    } else {
      remove(mid+1, r, 2*node+1, idx);
    }
    tree[node] = tree[2*node] + tree[2*node+1];
  }
}

int query(int l, int r, int node, int k) {
  if(l == r) {
    return l;
  } else {
    int mid = (l+r) / 2;
    if(tree[2*node] >= k) {
      return query(l, mid, 2*node, k);
    } else {
      // szuakana liczba elementow - usunieta liczba elementow w lewym poddrzewie
      return query(mid+1, r, 2*node+1, k-tree[2*node]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  input.resize(n);
  deletes.resize(n);
  tree.resize(4*n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  build(0, n-1, 1);
  for(int i = 0; i < n; i++) {
    cin >> deletes[i];
    int pos = query(0, n-1, 1, deletes[i]);
    cout << input[pos] << ' ';
    remove(0, n-1, 1, pos); 
  }
  return 0;
}