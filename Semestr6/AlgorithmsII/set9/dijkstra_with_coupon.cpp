#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+2;

vector<pair<int, long long>> graph[N];
bool visited[N];
long long min_dist[N][2];

void dijkstra(int u) {
  priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
  pq.push({0ll, u, 0});
  min_dist[u][0] = 0ll;
  while(!pq.empty()) {
    auto [dist, node, used] = pq.top();
    pq.pop();
    if(dist > min_dist[node][used]) continue;
    for(auto v : graph[node]) {
      long long alt = min_dist[node][used] + v.second;
      if(alt < min_dist[v.first][used]) {
        min_dist[v.first][used] = alt;
        pq.push({alt, v.first, used});
      }
      if(!used && min_dist[v.first][1] > dist + v.second / 2) {
        min_dist[v.first][1] = dist + v.second / 2;
        pq.push({min_dist[v.first][1], v.first, 1});
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
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j <= n; j++) {
      min_dist[j][i] = LLONG_MAX;
    }
  }
  dijkstra(1);
  cout << min_dist[n][1];
  return 0;
}