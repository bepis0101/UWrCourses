#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;
bool visited[N];

vector<pair<int, int>> graph[N];
int deg[N];
vector<int> L;
bool isUsed[2*N];

void euler(int u) {
  stack<int> S;
  S.push(u);

  while(!S.empty()) {
    int v = S.top();
    while(!graph[v].empty() && isUsed[graph[v].back().second]) {
      graph[v].pop_back();
    }
    if(graph[v].empty()) {
      L.push_back(v);
      S.pop();
    } else {
      auto [w, id] = graph[v].back();
      graph[v].pop_back();
      isUsed[id] = true;
      S.push(w);
    }
  }
}

void dfs(int u) {
  if(!visited[u]) {
    visited[u] = true;
    for(auto v : graph[u]) {
      dfs(v.first);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m; cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    graph[a].push_back({b, i});
    graph[b].push_back({a, i});
    deg[a]++;
    deg[b]++;
  }
  dfs(1);
  for(int i = 1; i <= n; i++) {
    if(deg[i] % 2 != 0 || (!visited[i] && deg[i] > 0)) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  euler(1);
  for(int v : L) {
    cout << v << " ";
  }
}