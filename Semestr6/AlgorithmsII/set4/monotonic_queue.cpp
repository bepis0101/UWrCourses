#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 3;


int main() {
  vector<int> input;
  int n; cin >> n;
  int q; cin >> q;
  input.resize(n);
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  vector<pair<int, pair<int, int>>> queries(q);
  for(int i = 0; i < q; i++) {
    int a, b; cin >> a >> b;
    queries[i] = {i, {--a, --b}};
  }
  sort(queries.begin(), queries.end(), [](const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b){
    return a.second.first < b.second.first;
  });

  
}