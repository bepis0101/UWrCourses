#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> sparse_table;

void build(int n, vector<int>& input) {
  sparse_table.resize(n, vector<int>(ceil(log2(n))+1));
  for(int i = 0; i < n; i++) {
    sparse_table[i][0] = input[i];
  }
  for(int i = 1; (1 << i) <= n; i++) {
    for(int j = 0; (1 << i)+j <= n; j++) {
      sparse_table[j][i] = min(sparse_table[j][i-1], sparse_table[j+(1 << (i-1))][i-1]);
    }
  }
}

int query(int a, int b) {
  int k = (int)(log2(b-a+1));
  return min(sparse_table[a][k], sparse_table[b-(1 << k)+1][k]);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> input(n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  build(n, input);
  while(q--) {
    int a, b; cin >> a >> b;
    cout << query(--a, --b) << "\n";
  }
}