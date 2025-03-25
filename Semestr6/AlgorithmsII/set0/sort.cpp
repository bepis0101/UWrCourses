#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+2;
int nums[N];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n; cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> nums[i];
  }
  sort(nums, nums+n);
  for(int i = 0; i < n; i++) {
    cout << nums[i] << ' ';
  }
  return 0;
}