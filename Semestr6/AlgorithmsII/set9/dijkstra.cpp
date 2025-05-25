#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+2;

vector<pair<int, long long>> graph[N];
bool visited[N];
long long min_dist[N];

void dijkstra(int u) {
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
  pq.push({0ll, u});
  min_dist[u] = 0ll;
  while(!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    if(visited[top.second]) continue;
    visited[top.second] = true;
    for(auto v : graph[top.second]) {
      long long alt = min_dist[top.second] + v.second;
      if(alt < min_dist[v.first]) {
        min_dist[v.first] = alt;
        pq.push({alt, v.first});
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m; cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int a, b, weight;
    cin >> a >> b >> weight;
    graph[a].push_back({b, weight});
  }
  fill(min_dist, min_dist + n + 1, LLONG_MAX);
  dijkstra(1);
  for(int i = 1; i <= n; i++) {
    cout << min_dist[i] << ' ';
  }
  return 0;
}