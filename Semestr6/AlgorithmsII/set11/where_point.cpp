#include <bits/stdc++.h>

using namespace std;

double f(double x1, double y1, double x2, double y2, double x3, double y3) {
  return (y3-y1) * (x2 - x1) - (y2 - y1) * (x3 - x1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for(int i = 0; i < n; i++) {
    double x1, y1, x2, y2, x3, y3; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    double res = f(x1, y1, x2, y2, x3, y3);
    if(res == 0) {
      cout << "TOUCH\n";
    } 
    else if(res > 0) {
      cout << "LEFT\n";
    } 
    else {
      cout << "RIGHT\n";
    }
  }
}