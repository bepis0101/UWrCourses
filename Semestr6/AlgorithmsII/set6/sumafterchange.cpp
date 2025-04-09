#include <bits/stdc++.h>

using namespace std;

vector<long long> input;
struct Node {
  long long sum;
  long long prefix;
  long long suffix;
  long long max_sum;
};

int n;
vector<Node> tree;

Node combine(const Node& a, const Node& b) {
  Node result;
  result.sum = a.sum + b.sum;
  result.prefix = max(a.prefix, a.sum + b.prefix);
  result.suffix = max(b.suffix, b.sum + a.suffix);
  result.max_sum = max({a.max_sum, b.max_sum, a.suffix + b.prefix, 0LL});
  return result;
}

void build(int node, int l, int r, const vector<long long>& input) {
  if(l == r) {
    long long safe = max(input[l], 0LL);
    tree[node] = {input[l], safe, safe, safe};
  } else {
    int mid = (l+r) / 2;
    build(2*node, l, mid, input);
    build(2*node+1, mid+1, r, input);
    tree[node] = combine(tree[2*node], tree[2*node+1]);
  }
}

void update(int node, int l, int r, int pos, long long val) {
  if(l == r) {
    long long safe = max(val, 0LL);
    tree[node] = {val, safe, safe, safe};
  } else {
    int mid = (l+r) / 2;
    if(pos <= mid) {
      update(2*node, l, mid, pos, val);
    } else {
      update(2*node+1, mid+1, r, pos, val);
    }
    tree[node] = combine(tree[2*node], tree[2*node+1]);
  }
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
    int k; long long x; cin >> k >> x;
    update(1, 0, n-1, k-1, x);
    cout << tree[1].max_sum << '\n';
  }
  return 0;
}