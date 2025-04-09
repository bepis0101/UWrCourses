#include <bits/stdc++.h>

using namespace std;

vector<long long> input;
struct Node {
  long long sum;
  long long prefix_max;
};
int n;
vector<Node> tree;

Node combine(const Node& a, const Node& b) {
  Node res;
  res.sum = a.sum + b.sum;
  res.prefix_max = max(a.prefix_max, a.sum + b.prefix_max);
  return res;
}

void build(int node, int l, int r, const vector<long long>& input) {
  if(l == r) {
    tree[node].sum = input[l];
    tree[node].prefix_max = max(0ll, input[l]);
  } else {
    int mid = (l+r) / 2;
    build(2*node, l, mid, input);
    build(2*node+1, mid+1, r, input);
    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    tree[node].prefix_max = max(tree[2*node].prefix_max, tree[2*node].sum + tree[2*node+1].prefix_max);
  }
}

void update(int idx, int l, int r, int node, long long val) {
  if(l == r) {
    tree[node].sum = val;
    tree[node].prefix_max = max(0LL, val);
  } else {
    int mid = (l+r) / 2;
    if(idx <= mid) {
      update(idx, l, mid, 2*node, val);
    } else {
      update(idx, mid+1, r, 2*node+1, val);
    }
    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    tree[node].prefix_max = max(tree[2*node].prefix_max, tree[2*node].sum + tree[2*node+1].prefix_max);
  }
}

void update(int k, long long val) {
  update(k, 0, n-1, 1, val);
}

Node query(int l, int r, int node, int lo, int hi) {
  if(r < lo || hi < l) return Node();
  if(l <= lo && hi <= r) return tree[node];
  int mid = (lo + hi) / 2;
  Node left = query(l, r, 2*node, lo, mid);
  Node right = query(l, r, 2*node+1, mid+1, hi);
  return combine(left, right);
}

long long query(int l, int r) {
  return query(l, r, 1, 0, n-1).prefix_max;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int q; cin >> n >> q;
  input.resize(n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  tree.resize(4*n);
  build(1, 0, n-1, input);
  while(q--) {
    int flag; cin >> flag;
    switch(flag) {
      case 1:
        int k; long long val; cin >> k >> val;
        update(k-1, val); 
        break;
      case 2:
        int x, y; cin >> x >> y;
        cout << query(x-1, y-1) << '\n';
        break;
    }
  }
  return 0;
}