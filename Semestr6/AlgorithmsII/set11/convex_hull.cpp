#include <bits/stdc++.h>

using namespace std;

struct Point {
  long long x, y;
  bool operator<(const Point& other) const {
    return (x < other.x) || (x == other.x && y < other.y);
  }
  bool operator==(const Point& other) const {
    return (x == other.x) && (y == other.y);
  }
};


vector<Point> points;

long long cross(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y-O.y) - (A.y-O.y) * (B.x-O.x);
}

vector<Point> convexHull(vector<Point>& points) {
  int n = points.size();
  sort(points.begin(), points.end());

  vector<Point> lower, upper;
  for (const Point& p : points) {
    while (lower.size() >= 2 &&
          cross(lower[lower.size()-2], lower[lower.size()-1], p) < 0)
      lower.pop_back();
    lower.push_back(p);
  }

  for (int i = n - 1; i >= 0; --i) {
    const Point& p = points[i];
    while (upper.size() >= 2 &&
          cross(upper[upper.size()-2], upper[upper.size()-1], p) < 0)
      upper.pop_back();
    upper.push_back(p);
  }

  lower.pop_back();
  upper.pop_back();
  vector<Point> res;
  for(const Point& p : lower) res.push_back(p);
  for(const Point& p : upper) res.push_back(p);
  sort(res.begin(), res.end());
  unique(res.begin(), res.end());
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;

  points.resize(n);

  for(int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    points[i] = {x, y};
  }
  auto hull = convexHull(points);
  cout << hull.size() << '\n';
  for(const Point& p : hull) {
    cout << p.x << ' ' << p.y << '\n';
  }
}