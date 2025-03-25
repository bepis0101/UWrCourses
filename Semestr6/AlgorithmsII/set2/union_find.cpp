#include <bits/stdc++.h>

using namespace std;

class DSU {
public:
  vector<int> parent, size;
  int tree_cnt;
  int max_tree_size;
  DSU(int n) {
    parent.resize(n+1);
    size.resize(n+1, 1);
    tree_cnt = n;
    max_tree_size = 1;
    for(int i = 1; i <= n; i++) {
      parent[i] = i;
    }
  }
  int find(int x) {
    if(parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }
  void unionn(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if(root_a != root_b) {
      if(size[root_a] < size[root_b]) {
        swap(root_a, root_b);
      }
      parent[root_b] = root_a;
      size[root_a] += size[root_b];
      size[root_b] = 0;
      tree_cnt--;
      max_tree_size = max(max_tree_size, size[root_a]);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n; // ilosc wierzcholkow
  int m; cin >> m; // liczba zapytan

  auto dsu = DSU(n);

  for(int i = 0; i < m; i++) { 
    int a, b; cin >> a >> b;
    dsu.unionn(a, b);
    cout << dsu.tree_cnt << ' ' << dsu.max_tree_size << '\n';
  }
  return 0;
}