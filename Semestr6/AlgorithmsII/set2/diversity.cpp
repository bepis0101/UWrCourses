#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+3;

class DSU {
  public:
    vector<int> parent, size;
    vector<pair<int, int>> maksmin;
    vector<long long> edges;

    DSU(int n) {
      parent.resize(n+1);
      size.resize(n+1, 1);
      maksmin.resize(n+1);
      edges.resize(n+1, 0);

      for(int i = 1; i <= n; i++) {
        parent[i] = i;
        maksmin[i] = {i, i};
      }
    }
    int find(int x) {
      if(parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }
    int unionn(int a, int b) {
      int root_a = find(a);
      int root_b = find(b);
      if(root_a != root_b) {
        if(size[root_a] < size[root_b]) {
          swap(root_a, root_b);
        }
        edges[root_a] += edges[root_b]+1;
        edges[root_b] = edges[root_a];
        parent[root_b] = root_a;
        size[root_a] += size[root_b];
        size[root_b] = 0;
        maksmin[root_a] = {min(maksmin[root_a].first, maksmin[root_b].first), max(maksmin[root_a].second, maksmin[root_b].second)};
      } else {
        edges[root_a]++;
        edges[root_b] = edges[root_a];
      }
      return root_a;
    }
  };


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m; cin >> n >> m;
  DSU dsu(n);
  for(int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    int node = dsu.unionn(a, b);
    // cerr << "edges: " << dsu.edges[node] << '\n';
    // cerr << "maks_node: " << dsu.maksmin[node].second << '\n';
    // cerr << "min_node: " << dsu.maksmin[node].first << '\n';
    long long res = dsu.edges[node] * (dsu.maksmin[node].second - dsu.maksmin[node].first);
    cout << res << '\n';
  }
  return 0;
}