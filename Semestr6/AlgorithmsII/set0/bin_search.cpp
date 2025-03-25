#include <bits/stdc++.h>

using namespace std;
const int N = 1e5+3;
int tab[N];

int find(int a, int n) {
  int l = 0, r = n-1;
  int mid = (l+r)/2;
  while(l <= r) {
    mid = (l+r)/2;
    if(tab[mid] == a) return mid+1;
    if(tab[mid] != a and l == r) return -1;
    if(tab[mid] < a) l = mid+1;
    else r = mid-1;
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> tab[i];
  }
  int m; cin >> m;
  while(m--) {
    int a; cin >> a;
    cout << find(a, n) << '\n';
  }
  return 0;
}