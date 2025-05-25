#include <bits/stdc++.h>

using namespace std;

const int N = 2504;

const long long INF = 1e15;
const long long NINF = -1e15;

struct Edge {
  // d - destinantion, s - source
  int s, d;
  long long weight;
};

vector<Edge> edges;
long long distances[N];

bool bellman_ford(int n, int m) {
  for(int i = 0; i < n-1; i++) {
    for(auto edge : edges) {
      if (distances[edge.s] + edge.weight < distances[edge.d]) {
        distances[edge.d] = distances[edge.s] + edge.weight;
      }
    }
  }
  for(auto edge : edges) {
    if(distances[edge.s] + edge.weight < distances[edge.d]) {
      return false;
    }
  }
  return true;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  edges.resize(m);
  for(int i = 0; i < m; i++) {
    int a, b, weight; cin >> a >> b >> weight;
    edges[i] = {a, b, -weight};
  }
  fill(distances, distances + n + 1, INF);
  distances[1] = 0;
  bool is_acyclic = bellman_ford(n, m);
  if(!is_acyclic) {
    cout << -1;
  } else {
    cout << -distances[n];
  }
}