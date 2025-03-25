#include <bits/stdc++.h>

using namespace std;

struct query {
  int l, r;
  int idx;
};

const int N = 1e5+3;
const int Q = 1e5+3;

const int B = ceil(sqrt(N));

int input[N];
query queries[Q];
int res[Q];
unordered_map<int, int> compressed;

int cnt;

int target[N];
int curr_cnt[N];

void add(int x) {
  curr_cnt[x]++;
  if(curr_cnt[x] == target[x]) {
    cnt++;
  } else if(curr_cnt[x] == target[x]+1) {
    cnt--;
  }
}

void remove(int x) {
  curr_cnt[x]--;
  if(curr_cnt[x] == target[x]) {
    cnt++;
  } else if(curr_cnt[x] == target[x]-1) {
    cnt--;
  }
}


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  int q; cin >> q;
  for(int i = 1; i <= n; i++) {
    cin >> input[i];
  }
  
  int unique = 0;
  for(int i = 1; i <= n; i++) {
    if(compressed.find(input[i]) == compressed.end()) {
      compressed[input[i]] = ++unique;
      target[compressed[input[i]]] = input[i];
    }
    input[i] = compressed[input[i]];
  }

  for(int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    queries[i].l = l;
    queries[i].r = r;
    queries[i].idx = i;
  }

  sort(queries, queries+q, [](const query& a, const query& b) {
    if(a.l / B == b.l / B) return a.r < b.r;
    return a.l / B < b.l / B;
  });


  int current_l = 1, current_r = 0;
  for(int i = 0; i < q; i++) {
    int ptr = queries[i].idx;
    while(current_l > queries[i].l) {
      current_l--;
      add(input[current_l]);
    } 
    while(current_r < queries[i].r) {
      current_r++;
      add(input[current_r]);
    }
    while(current_l < queries[i].l) {
      remove(input[current_l]);
      current_l++;
    }
    while(current_r > queries[i].r) {
      remove(input[current_r]);
      current_r--;
    }
    res[ptr] = cnt;
  }

  for(int i = 0; i < q; i++) {
    cout << res[i] << '\n';
  }

}