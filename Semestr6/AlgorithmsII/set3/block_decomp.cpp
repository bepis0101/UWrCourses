#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 4;
const int B = 450;

int input[N];
long long block[B];

int block_size;

void preproccess(int n) {
  block_size = ceil(sqrt(n));
  for(int i = 0; i < n; i++) {
    block[i / block_size] += input[i];
  }
}

void update(int idx, int val) {
  int block_idx = idx / block_size;
  block[block_idx] -= input[idx];
  input[idx] = val;
  block[block_idx] += val;
}

long long query(int l, int r) {
  long long sum = 0;
  int block_start = l / block_size;
  int block_end = r / block_size;
  if(block_start == block_end) {
    for(int i = l; i <= r; i++) {
      sum += input[i];
    }
  } else {
    for(int i = l; i < (block_start+1)*block_size; i++) {
      sum += input[i];
    }
    for(int i = block_start+1; i < block_end; i++) {
      sum += block[i];
    }
    for(int i = block_end * block_size; i <= r; i++) {
      sum += input[i];
    }
  }

  return sum;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, q; cin >> n >> q;
  for(int i = 0; i < n; i++) {
    cin >> input[i];
  }
  preproccess(n);
  while(q--) {
    int type, a, b; cin >> type >> a >> b;
    switch(type) {
      case 1:
        update(--a, b);
        break;
      case 2:
        cout << query(--a, --b) << '\n';
        break;
      default:
        break;
    }
  }
  return 0;
}