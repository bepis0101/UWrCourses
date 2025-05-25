#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;
bool visited[N];

vector<pair<int, int>> graph[N];
vector<pair<int, int>> rev_graph[N];
int indeg[N];
int outdeg[N];

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

void dfs2(int u) {
  if(!visited[u]) {
    visited[u] = true;
    for(auto v : rev_graph[u]) {
      dfs2(v.first);
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
    rev_graph[b].push_back({a, i});
    indeg[b]++;
    outdeg[a]++;
  }
  
  dfs(1);

  for(int i = 1; i <= n; i++) {
    if((indeg[i] > 0 || outdeg[i] > 0) && !visited[i]) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

fill(visited, visited + N, false);
dfs2(n);

for(int i = 1; i <= n; i++) {
  if((indeg[i] > 0 || outdeg[i] > 0) && !visited[i]) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
}

  for (int i = 1; i <= n; i++) {
  if (i == 1) {
    if (outdeg[i] != indeg[i] + 1) { cout << "IMPOSSIBLE\n"; return 0; }
  } else if (i == n) {
    if (indeg[i] != outdeg[i] + 1) { cout << "IMPOSSIBLE\n"; return 0; }
  } else {
    if (indeg[i] != outdeg[i]) { cout << "IMPOSSIBLE\n"; return 0; }
  }
}

  euler(1);
  if(L.size() != m+1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  reverse(L.begin(), L.end());
  for(int v : L) {
    cout << v << " ";
  }
}