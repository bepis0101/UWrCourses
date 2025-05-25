#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;
bool visited[N];
vector<int> graph[N];
vector<int> reverse_graph[N];
int assignment[N];
vector<int> L;
int labels[N];
int comp = 0;

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


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m; cin >> n >> m;
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
    if(!assignment[v]) comp++;
    assign(v, v);
  }
  cout << comp << '\n';
  int counter = 0;
  for(int i = 1; i <= n; i++) {
    if(!labels[assignment[i]]) {
      counter++;
      labels[assignment[i]] = counter;
    }
    assignment[i] = labels[assignment[i]];
  }
  for(int i = 1; i <= n; i++) {
    cout << assignment[i] << ' ';
  }
  return 0;
}