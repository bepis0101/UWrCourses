#include <bits/stdc++.h>

using namespace std;

const int N = 2504;

struct Edge {
  // d - destinantion, s - source
  int s, d;
  long long weight;
};

vector<Edge> edges;
long long distances[N];
int predecessor[N];
const long long INF = 1e9 + 15;

vector<int> bellman_ford(int n, int m) {
  vector<int> res;
  int cycle;

  for (int i = 0; i < n; i++) {
    cycle = -1;
    for (auto edge : edges) {
      if (distances[edge.s] + edge.weight < distances[edge.d]) {
        distances[edge.d] = distances[edge.s] + edge.weight;
        predecessor[edge.d] = edge.s;
        cycle = edge.d;
      }
    }
  }
  if (cycle == -1) return res; 

  for (int i = 0; i < n; i++) {
    cycle = predecessor[cycle];
  }

  for (int v = cycle;; v = predecessor[v]) {
    res.push_back(v);
    if (v == cycle && res.size() > 1) break;
  }
  reverse(res.begin(), res.end());
  return res;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  edges.resize(m);
  for(int i = 0; i < m; i++) {
    int a, b, weight; cin >> a >> b >> weight;
    edges[i] = {a, b, weight};
  }
  fill(distances, distances + n + 1, 0);
  fill(predecessor, predecessor + n + 1, 0);
  auto cycle = bellman_ford(n, m);
  if(cycle.empty()) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  for(int v : cycle) {
    cout << v << ' ';
  }
  return 0;
}