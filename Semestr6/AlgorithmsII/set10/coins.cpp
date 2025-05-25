#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

vector<int> graph[N];
vector<int> reverse_graph[N];
vector<long long> coins;
vector<int> L;
bool visited[N];
int assignment[N];
long long res[N];
vector<int> new_graph[N];

void dfs(int u) {
  if(!visited[u]) {
    visited[u] = true;
    for(int v : graph[u]) {
      dfs(v);
    }
    L.push_back(u);
  }
}

void assign(int node, int u) {
  if(!assignment[node]) {
    assignment[node] = u;
    for(int v : reverse_graph[node]) {
      assign(v, u);
    }
  }
}

void dfs2(int u) {
  if(!visited[u]) {
    visited[u] = true;
    long long maks = 0;
    for(int v : new_graph[u]) {
      dfs2(v);
      maks = max(maks, res[v]);
    }
    res[u] += maks;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int n, m; cin >> n >> m;
  coins.resize(n+1);
  for(int i = 1; i <= n; i++) {
    cin >> coins[i];
  }
  for(int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    graph[a].push_back(b);
    reverse_graph[b].push_back(a);
  }

  for(int i = 1; i <= n; i++) {
    if(!visited[i]) dfs(i);
  }

  reverse(L.begin(), L.end());
  
  for(int v : L) {
    assign(v, v);
  }

  for(int i = 1; i <= n; i++) {
    res[assignment[i]] += coins[i];
  }
  for(int i = 1; i <= n; i++) {
    for(int v : graph[i]) {
      if(assignment[v] != assignment[i]) {
        new_graph[assignment[i]].push_back(assignment[v]);
      }
    }
  }
  fill(visited, visited + N, false);
  for(int i = 1; i <= n; i++) {
    dfs2(assignment[i]);
  }
  long long maks = 0;
  for(int i = 1; i <= n; i++) {
    maks = max(maks, res[assignment[i]]);
  }
  cout << maks;
}