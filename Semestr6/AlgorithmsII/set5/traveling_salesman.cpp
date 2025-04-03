#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 20;

vector<int> graph[N];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    graph[--a].push_back(--b);
  }
  
  vector<vector<int>> dp((1 << n), vector<int>(n, 0));
  dp[1][0] = 1;
  for(int mask = 1; mask < (1 << n); mask++) {
    for(int u = 0; u < n; u++) {
      // jesli u jest czescia sciezki
      if(mask & (1 << u)) {
        for(int v : graph[u]) {
          // czy v zostalo odwiedzone
          if(!(mask & (1 << v))) {
            int new_mask = mask | (1 << v);
            dp[new_mask][v] = (dp[new_mask][v] + dp[mask][u]) % MOD;
          }
        }
      }
    }
  }
  cout << dp[(1 << n)-1][n-1] << '\n';
}