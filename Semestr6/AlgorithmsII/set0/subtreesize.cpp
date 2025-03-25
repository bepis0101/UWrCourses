#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+2;

vector<int> tree[N];

int size_of_subtree[N];

void dfs(int u, int size) {
  
}

int main() {
  int n; cin >> n;
  for(int i = 2; i < n; i++) {
    int a; cin >> a;
    tree[a].push_back(i);
    tree[i].push_back(a);
  }

}