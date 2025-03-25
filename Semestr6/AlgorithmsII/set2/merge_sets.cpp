#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 3;

int colors[N];
vector<int> T[N];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> colors[i];
  }
  for(int i = 0; i < n-1; i++) {
    int a, b; cin >> a >> b;
    T[a].push_back(b);
    T[b].push_back(a);
  }
}