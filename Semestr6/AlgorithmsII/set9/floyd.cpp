#include <bits/stdc++.h>

using namespace std;

const int N = 5e2+4;
long long floyd_warshall[N][N];

void floyd(int n) {
  for(int via = 1; via <= n; via++) {
    for(int from = 1; from <= n; from++) {
      for(int to = 1; to <= n; to++) {
        if(floyd_warshall[from][via] != LLONG_MAX && 
           floyd_warshall[via][to] != LLONG_MAX &&
           floyd_warshall[from][via] + floyd_warshall[via][to] < floyd_warshall[from][to]
        ) {
          floyd_warshall[from][to] = floyd_warshall[from][via] + floyd_warshall[via][to];
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m, q; cin >> n >> m >> q;
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= n; j++) {
      if(i == j) floyd_warshall[i][j] = 0;
      else floyd_warshall[i][j] = LLONG_MAX;
    }
  }
  for(int i = 0; i < m; i++) {
    int a, b, weight; cin >> a >> b >> weight;
    floyd_warshall[a][b] = min(floyd_warshall[a][b], 1LL * weight);
    floyd_warshall[b][a] = min(floyd_warshall[b][a], 1LL * weight);
  }
  floyd(n);

  while(q--) {
    int a, b; cin >> a >> b;
    if(floyd_warshall[a][b] == LLONG_MAX) {
      cout << -1 << '\n';
    } else {
      cout << floyd_warshall[a][b] << '\n';
    }
  }
  return 0;
}