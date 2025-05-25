#include <bits/stdc++.h>

using namespace std;

struct line {
  double A, B, C;
};

double linef(double x1, double y1, double x2, double y2, double x3, double y3) {
  return (y3-y1) * (x2 - x1) - (y2 - y1) * (x3 - x1);
}

double dist(double x1, double y1, double x2, double y2, double x0, double y0) {
  double res = abs(linef(x1, y1, x2, y2, x0, y0));
  return res / sqrt((y1-y2)*(y1-y2) + (x2-x1)*(x2-x1));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for(int i = 0; i < n; i++) {
    double a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    cout << setprecision(9) << dist(a, b, c, d, e, f) << '\n';
  }
  return 0;
}