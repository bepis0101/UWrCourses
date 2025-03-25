#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+3;
const int S = 1e3;

struct Point {
  int idx, x, y;
};


int main() {
  vector<Point> points;
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  points.resize(n);

  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    Point a;
    a.idx = i+1;
    a.x = x;
    a.y = y;
    points[i] = a;
  }

  sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    if(a.y / S == b.y / S) {
      return (a.y / S & 1) ? a.x > b.x : a.x < b.x;
    } 
    return a.y < b.y;
  });

  for(int i = 0; i < n; i++) {
    cout << points[i].idx << ' ';
  }
}