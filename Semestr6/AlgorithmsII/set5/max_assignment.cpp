#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<vector<int>> profits(n, vector<int>(n));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> profits[i][j];
    }
  }
  vector<int> dp((1 << n));
  for(int mask = 0; mask < (1 << n); mask++) {
    // ilosc osob ktore juz zajely miejsce
    int person_idx = __builtin_popcount(mask);
    for(int i = 0; i < n; i++) {
      // jeżeli miejsce pracy nie jest jeszcze zajete
      if(!(mask & (1 << i))) {
        int new_mask = mask | (1 << i);
        dp[new_mask] = max(dp[new_mask], dp[mask] + profits[person_idx][i]);
      }
    }
  }
  cout << dp[(1 << n)-1] << '\n';
}