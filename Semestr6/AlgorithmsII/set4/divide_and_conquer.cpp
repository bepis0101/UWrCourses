#include <bits/stdc++.h>

using namespace std;

void build_tree(vector<int>& input, vector<int>& tree, int node, int start, int end) {
  if(start == end) {
    tree[node] = input[start];
    return;
  }
  int mid = (start+end)/2;
  int left = 2*node+1, right = 2*node+2;
  build_tree(input, tree, left, start, mid);
  build_tree(input, tree, right, mid+1, end);
  tree[node] = min(tree[left], tree[right]);
}

int query(vector<int>& tree, int node, int start, int end, int L, int R) {
  if(R < start || end < L) {
    return INT_MAX;
  }
  if(L <= start && R >= end) {
    return tree[node];
  }
  int mid = (start+end)/2;
  int left_child = 2*node + 1;
  int right_child = 2*node + 2;
  return min(query(tree, left_child, start, mid, L, R), 
            query(tree, right_child, mid+1, end, L, R));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> input(n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  vector<int> segment_tree(4*n);
  build_tree(input, segment_tree, 0, 0, n-1);
  while(q--) {
    int a, b; cin >> a >> b;
    cout << query(segment_tree, 0, 0, n-1, a-1, b-1) << "\n";
  }

}