#include <bits/stdc++.h>

using namespace std;

vector<int> tree;
vector<int> input;

const int MAX = 1e6+1;

void update(int id) {
  id += MAX;
  tree[id]++;
  while(id > 1) {
    id /= 2;
    tree[id] = tree[2*id] + tree[2*id + 1];
  }
}

int query(int l, int r) {
  int res = 0;
  l += MAX;
  r += MAX;
  while(l < r) {
    if(l & 1) {
      res += tree[l];
      l++;
    }
    if(r & 1) {
      r--;
      res += tree[r];
    }
    l /= 2;
    r /= 2;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  input.resize(n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  tree.resize(2*MAX);
  long long inversions = 0;
  for(int i = n-1; i >= 0; i--) {
    inversions += query(0, input[i]);
    update(input[i]);
  }
  cout << inversions << '\n';
  return 0;
}