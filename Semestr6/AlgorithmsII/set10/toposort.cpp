#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+2;
vector<int> graph[N];
int indeg[N];

bool IMPOSSIBLE = false;

vector<int> sorted;

void toposort(int n) {
  priority_queue<int, vector<int>, greater<>> pq;
  for(int i = 1; i <= n; i++) {
    if(!indeg[i]) {
      pq.push(i);
    }
  }
  while(!pq.empty()) {
    int u = pq.top();
    pq.pop();
    sorted.push_back(u);
    for(int v : graph[u]) {
      indeg[v]--;
      if(!indeg[v]) { 
        pq.push(v);
      }
    }
  }
  for(int i = 1; i <= n; i++) {
    if(indeg[i] > 0) {
      IMPOSSIBLE = true;
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
    indeg[b]++;
  }
  toposort(n);
  
  if(IMPOSSIBLE) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  for(int v : sorted) {
    cout << v << ' ';
  }
  return 0;
}