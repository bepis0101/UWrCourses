#include <bits/stdc++.h>
using namespace std;

long long euclidean(long long a, long long b) {
  while(b) {
    long long t = b;
    b = a % b;
    a = t;  
  }
  return a;
}

int main() {
  long long a, b; cin >> a >> b;
  cout << euclidean(a, b);
}