#include <bits/stdc++.h>

using namespace std;

const int C = 101;
const int F = 1e6+2;
pair<int, int> coins[C];
long long minDP[F];
long long maxDP[F];
pair<int, int> path[C]; // min, max 


void solve(int f, int c) {
  for (int i = 0; i < c; i++) {
    for (int j = 0; j <= f; j++) {
      if (j - coins[i].second >= 0) {
        if(minDP[j - coins[i].second] != LLONG_MAX){
          minDP[j] = min(minDP[j], minDP[j - coins[i].second] + coins[i].first);
        }
        if(maxDP[j - coins[i].second] != LLONG_MIN) {
          maxDP[j] = max(maxDP[j], maxDP[j - coins[i].second] + coins[i].first);
        }
      }
    }
  }
}

void retrievePathMin(int f, int c) {
  int i = f;
  while (i > 0) {
    for (int j = 0; j < c; j++) {
      if (i - coins[j].second >= 0) {
        if (minDP[i] == minDP[i - coins[j].second] + coins[j].first) {
          path[j].first++;
          i -= coins[j].second;
          break;
        }
      }
    }
  }
  for(int i = 0; i < c; i++) {
    cout << path[i].first << ' ';
  }
}

void retrievePathMax(int f, int c) {
  int i = f;
  while (i > 0) {
    for (int j = 0; j < c; j++) {
      if (i - coins[j].second >= 0) {
        if (maxDP[i] == maxDP[i - coins[j].second] + coins[j].first) {
          path[j].second++;
          i -= coins[j].second;
          break;
        }
      }
    }
  }
  for(int i = 0; i < c; i++) {
    cout << path[i].second << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int f; cin >> f; // Target weight
  int c; cin >> c; // num of coins
  for (int i = 0; i < c; i++) {
    cin >> coins[i].first; // value
    cin >> coins[i].second; // weight
  }

  
  minDP[0] = 0;
  maxDP[0] = 0;
  
  for (int i = 1; i <= f; i++) {
    minDP[i] = LLONG_MAX;
    maxDP[i] = LLONG_MIN;
  }

  solve(f, c);

  if(minDP[f] == LLONG_MAX || maxDP[f] == LLONG_MIN) {
    cout << "NIE\n";
    return 0;
  }
  cout << "TAK\n";
  cout << minDP[f] << '\n';
  retrievePathMin(f, c);
  cout << '\n';
  cout << maxDP[f] << '\n';
  retrievePathMax(f, c);

  return 0;
}