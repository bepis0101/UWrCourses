#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 3;

vector<int> tree[N];

int dp[N][2];

void dfs(int node, int parent) {
  int sumChildren = 0;
    
  for (int v : tree[node]) {
    if (v == parent) continue;
    dfs(v, node);
    sumChildren += dp[v][1];
  }
  dp[node][0] = sumChildren;
  
  for (int v : tree[node]) {
    if (v == parent) continue;
    dp[node][1] = max(dp[node][1], 1 + dp[v][0] + sumChildren - dp[v][1]);
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
  dfs(1, -1);
  cout << max(dp[1][1], dp[1][0]) << '\n';
}