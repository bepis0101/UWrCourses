#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 3;
vector<int> tree[N];

int maxDist, maxNode;

void dfs(int node, int dist, int parent) {
  if(dist > maxDist) {
    maxNode = node;
    maxDist = dist;
  }
  for(int u : tree[node]) {
    if(u != parent) {
      dfs(u, dist+1, node);
    }
  }
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for(int i = 0; i < n-1; i++) {
    int a, b; cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  maxDist = -1;
  dfs(1, 0, 1);

  maxDist = -1;
  dfs(maxNode, 0, maxNode);

  cout << maxDist << '\n';
  return 0;
}