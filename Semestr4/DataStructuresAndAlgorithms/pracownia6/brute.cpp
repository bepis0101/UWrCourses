#include <bits/stdc++.h>

using namespace std;
char pattern[203][203];
char text[2003][2003];

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
  for(int y = 1; y <= c-a+1; y++) {
    for(int x = 1; x <= d-b+1; x++) {
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
      if(check)
      count++;
    }
  }
  cout << count;

}