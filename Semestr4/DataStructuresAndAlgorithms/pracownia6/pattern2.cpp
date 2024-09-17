#include <bits/stdc++.h>
using namespace std;
#define alphabet 26
const int MOD = 1e7+19;

char pattern[203][203];
char text[2003][2003];
int row_hashes[2003][2003];
int hashes[2003][2003];

int patternCounting(int a, int b) {
  int hash = 0;
  for(int y = 1; y <= a; y++) {
    int row = 0;
    for(int x = 1; x <= b; x++) {
      row = ((row*alphabet)%MOD+pattern[y][x])%MOD;
    }
    hash = (hash + row)%MOD;
  }
  return hash;
}

void computerow_Hashes(int a, int b, int Y, int X) {
  int base = 1;
  for(int i = 0; i < b-1; i++) {
    base = (base*alphabet)%MOD;
  }
  int hash = 0;
  for(int x = 1; x <= b; x++) {
    hash = ((hash*alphabet)%MOD+text[1][x])%MOD;
  }
  row_hashes[1][1] = hash;
  for(int y = 1; y <= Y; y++) {
    for(int x = 2; x <= X-b+1; x++) {
      row_hashes[y][x] = ((alphabet*(row_hashes[y][x-1]-text[y][x-1]*base))%MOD+text[y][x+b-1])%MOD;
      if(row_hashes[y][x] < 0) row_hashes[y][x] += MOD;
    }
    hash = 0;
    for(int x = 1; x <= b; x++) {
      hash = ((hash*alphabet)%MOD+text[y+1][x])%MOD;
    }
    row_hashes[y+1][1] = hash;
  }
}

void computeHashes(int a, int b, int Y, int X) {
  for(int y = 1; y <= Y-a+1; y++) {
    for(int x = 1; x <= X-b+1; x++) {
      int sum = 0;
      for(int i = 0; i < a; i++) {
        sum = (sum+row_hashes[y+i][x])%MOD;
      }
      hashes[y][x] = sum;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  for(int y = 1; y <= a; y++) {
    for(int x = 1; x <= b; x++) {
      cin >> pattern[y][x];
      pattern[y][x] = pattern[y][x] - 'A' + 1;
    }
  }
  for(int y = 1; y <= c; y++) {
    for(int x = 1; x <= d; x++) {
      cin >> text[y][x];
      text[y][x] = text[y][x] - 'A' + 1;
    }
  }
  

  int count = 0;
  int pat = patternCounting(a, b);
  computerow_Hashes(a, b, c, d);
  computeHashes(a, b, c, d);
  for(int y = 1; y <= c-a+1; y++) {
    for(int x = 1; x <= d-b+1; x++) {
      bool check = true;
      if(hashes[y][x] == pat) {
        for(int i = 0; i < a; i++) {
          for(int j = 0; j < b; j++) {
            if(text[y+i][x+j] != pattern[i+1][j+1]) {
              check = false;
              break;
            }
          }
          if(!check) break;
        }
        if(check)
        count++;
      }
    }
  }

  cout << count;
}