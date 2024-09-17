#include <bits/stdc++.h>
#define alphabet 26
using namespace std;


const int MOD = 1e7+19;
// const int MOD = 2000003867;
char pattern[203][203];
char text[2003][2003];
int hashes[2003][2003]; // prefix sum of hashes horiznotally
int powers[203][203];


// X, Y top left corner of the current checking of pattern
// a, b dimensions of the pattern

void computeHashes(int a, int b, int Y, int X) {
  int poww = 1;
  for(int y = a; y > 0; y--) {
    for(int x = b; x > 0; x--) {
      powers[y][x] = poww;
      poww = (alphabet*poww)%MOD;
    }
  }

  int hash = 0;
  for(int y = 1; y <= a; y++) {
    for(int x = 1; x <= b; x++) {
      hash = ((hash*alphabet)%MOD + text[y][x])%MOD;
    }
  }
  hashes[1][1] = hash;

  for(int y = 1; y <= Y-a+1; y++) {
    for(int x = 2; x <= X-b+1; x++) {
      hashes[y][x] = hashes[y][x-1];
      for(int i = 0; i < a; i++) {
        hashes[y][x] = (hashes[y][x]-(text[y+i][x-1]*powers[i+1][1])%MOD)%MOD;
        if(hashes[y][x] < 0) hashes[y][x] += MOD;
      }
      hashes[y][x] = (hashes[y][x]*alphabet)%MOD;
      for(int i = 0; i < a; i++) {
        hashes[y][x] = (hashes[y][x]+(text[y+i][x+b-1]*powers[i+1][b])%MOD)%MOD;
        if(hashes[y][x] < 0) hashes[y][x] += MOD;
      }
    }
    hashes[y+1][1] = hashes[y][1];
    for(int i = 0; i < b; i++) {
      hashes[y+1][1] = (hashes[y+1][1]-(text[y][i+1]*powers[1][i+1])%MOD)%MOD;
      if(hashes[y+1][1] < 0) hashes[y+1][1] += MOD;
    }
    for(int i = 0; i < b; i++) {
      hashes[y+1][1] = (hashes[y+1][1]*alphabet)%MOD;
    }
    for(int i = 0; i < b; i++) {
      hashes[y+1][1] = (hashes[y+1][1]+(text[y+a][i+1]*powers[a][i+1])%MOD)%MOD;
      if(hashes[y+1][1] < 0) hashes[y+1][1] += MOD;
    }
  }
}

int patternCounting(int a, int b) {
  int hash = 0;
  for(int y = 1; y <= a; y++) {
    for(int x = 1; x <= b; x++) {
      hash = (hash*alphabet + pattern[y][x])%MOD;
    }
  }
  return hash;
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
  computeHashes(a, b, c, d);
  for(int y = 1; y <= c-a+1; y++) {
    for(int x = 1; x <= d-b+1; x++) {
      if(hashes[y][x] == pat) {
        bool check = true;
        for(int i = 0; i < a; i++) {
          for(int j = 0; j < b; j++) {
            if(text[y+i][x+j] != pattern[i+1][j+1]) {
              check = false;
              break;
            }
          }
          if(!check) break;
        }
        if(check) {
          count++;
        }
      }
    }
  }
  cout << count;
  
  
}