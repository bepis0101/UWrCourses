#include <bits/stdc++.h>
#define MOD 101
#define alphabet 26
using namespace std;

char pattern[201][201];
char text[2001][2001];
int hashes[2001][2001]; // prefix sum of hashes horiznotally

// x, y top left corner of the current checking of pattern
// a, b dimensions of the pattern

int power(int a, int b) {
  int res = 1;
  while(b > 0) {
    if(b % 2 == 1) {
      b--;
      res = (res * a) % MOD;
    } else {
      b /= 2;
      a = (a * a) % MOD;
    }
  }
  return res;
}

void computeHashes(int a, int b, int y, int x) {
  int maxPow = power(alphabet, a-1);
  for(int i = 1; i <= y; i++) {
    int hash = 0;
    for(int j = 1; j <= b; j++) {
      hash = (hash * alphabet + text[i][j]) % MOD;
    }
    hashes[i][1] = hash;
    for(int j = 2; j <= x-b+1; j++) {
      hash = (hash * alphabet + text[i][j+b-1] - text[i][j-1] * maxPow) % MOD;
      hashes[i][j] = hash;
    }
  }
  for(int i = 1; i <= y; i++) {
    for(int j = 2; j <= x-b+1; j++) {
      hashes[i][j] += hashes[i][j-1];
    }
  }
  for(int i = 2; i <= y-a+1; i++) {
    for(int j = 1; j <= x; j++) {
      hashes[i][j] += hashes[i-1][j];
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
      pattern[y][x] -= 'B';
    }
  }
  for(int y = 1; y <= c; y++) {
    for(int x = 1; x <= d; x++) {
      cin >> text[y][x];
      text[y][x] -= 'B';
    }
  }
  computeHashes(a, b, c, d);
  int patternHash = 0;
  for(int i = 1; i <= a; i++) {
    for(int j = 1; j <= b; j++) {
      patternHash = (patternHash * alphabet + pattern[i][j]) % MOD;
    }
  }
  int counter = 0;

  cout << "pattern hash: " << patternHash << '\n';
  for(int i = 1; i <= c-a+1; i++) {
    for(int j = 1; j <= d-b+1; j++) {
      int hash = (hashes[i+a-1][j+b-1] - hashes[i-1][j+b-1] - hashes[i+a-1][j-1] + hashes[i-1][j-1]) % MOD;
      while(hash < 0) {
        hash += MOD;
      }
      cout << "finding hash: " <<  hash << '\n';
      if(hash == patternHash) {
        for(int y = 1; y <= a; y++) {
          for(int x = 1; x <= b; x++) {
            if(pattern[y][x] != text[i+y-1][j+x-1]) {
              break;
            }
            if(y == a && x == b) {
              counter++;
            }
          }
        }
      }
    }
  }

  // cout << counter << '\n';
  // for(int i = 1; i <= c-a+1; i++) {
  //   for(int j = 1; j <= d-b+1; j++) {
  //     cout << hashes[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }
}