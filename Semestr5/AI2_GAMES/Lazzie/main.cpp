#include <bits/stdc++.h>

using namespace std;

class Point {
public:
  int x;
  int y;
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  Point() {
    this->x = 0;
    this->y = 0;
  }
  Point& operator=(const Point& p) {
    this->x = p.x;
    this->y = p.y;
    return *this;
  }
  bool operator==(const Point& p) const {
    return this->x == p.x && this->y == p.y;
  }
  Point operator+(const Point& p) const {
    return Point(x+p.x, y+p.y);
  }
  int manhatan(const Point& p) const {
    return abs(x-p.x) + abs(y-p.y);
  }

  friend ostream& operator<<(ostream& os, const Point& p) {
    os << "(x: " <<  p.x << ", y: " << p.y << ")";
    return os;
  }
};

const int MAX_WIDTH = 204;
const int MAX_HEIGHT = 204;
const int WIDTH = 2*MAX_WIDTH;
const int HEIGHT = 2*MAX_HEIGHT;

enum DIR {N, S, W, E};
const Point DIR_VAL[] = {
  Point(0, -1), 
  Point(0, 1),
  Point(-1, 0),
  Point(1, 0),
};

char grid[HEIGHT][WIDTH];
int vision_range; // Diameter of Lazzie's vision
int home_distance_horizontal; // Distance in W/E direction towards home (negative means W side, positive means E side)
int home_distance_vertical; // Distance in N/S direction towards home (negative means N side, positive means S side)
Point pos; 
Point home;

void parse_init_input() {
  cin >> vision_range >> home_distance_horizontal >> home_distance_vertical; cin.ignore();
  pos = Point(MAX_WIDTH, MAX_HEIGHT);
  
  for(int y = 0; y < HEIGHT; y++) {
    for(int x = 0; x < WIDTH; x++) {
      grid[y][x] = '?';
    }
  }
  home = Point(pos.x + home_distance_horizontal, pos.y + home_distance_vertical);
}

void get_vision() {
  for(int i = 0; i < vision_range; i++) {
    string row; // A single row of the map within the vision range. Possible tile values: passable terrain ('.'), impassable obstacles ('#'), outside vision circle ('?'), home entrance ('H'), Lazzie ('L').
    cin >> row; cin.ignore();
    for(int j = 0; j < row.size(); j++) {
      if(row[j] != 'L' && row[j] != '?') {
        grid[i + pos.y - vision_range/2][j + pos.x - vision_range/2] = row[j];
      }
    }
  }
}

int visited[HEIGHT][WIDTH];
int vis_cnt = 1;

Point parents[HEIGHT][WIDTH];

int g[HEIGHT][WIDTH];

int checked[HEIGHT][WIDTH];
int checked_cnt = 1;

vector<Point> AStar() {
  vector<Point> path;
  const auto comp = [](const pair<int, Point> &a, const pair<int, Point> &b) {
    return a.first > b.first;
  };
  priority_queue<pair<int, Point>, vector<pair<int, Point>>, decltype(comp)> dist(comp);
  dist.push({0, pos});
  vis_cnt++;
  checked_cnt++;
  g[pos.y][pos.x] = 0;
  parents[pos.y][pos.x] = pos;
  checked[pos.y][pos.x] = checked_cnt;
  while(!dist.empty()) {
    Point p = dist.top().second;
    dist.pop();
    if(p == home) {
      while(!(p == pos)) {
        path.push_back(p);
        p = parents[p.y][p.x];
      }
      break;
    }
    if(visited[p.y][p.x] == vis_cnt) {
      continue;
    }
    visited[p.y][p.x] = vis_cnt;
    
    for(int i = 0; i < 4; i++) {
      const Point new_p = p + DIR_VAL[i];
      if(new_p.x < 0 || new_p.y < 0 || new_p.x >= WIDTH || new_p.y >= HEIGHT || grid[new_p.y][new_p.x] == '#') {
        continue;
      }
      if(visited[new_p.y][new_p.x] == vis_cnt || 
      (checked[new_p.y][new_p.x] == checked_cnt && g[new_p.y][new_p.x] <= g[p.y][p.x]+1)) {
        continue;
      }
      g[new_p.y][new_p.x] = g[p.y][p.x]+1;
      parents[new_p.y][new_p.x] = p;
      checked[new_p.y][new_p.x] = checked_cnt;
      dist.push({g[new_p.y][new_p.x] + new_p.manhatan(home), new_p});
    }
  }
  for(int y = -7; y <= 7; y++) {
    for(int x = -7; x <= 7; x++) {
      cerr << grid[pos.y+y][pos.x+x] << ' ';
    }
    cerr << '\n';
  }
  return path;
}

int main() {
  parse_init_input();
  while(1) {
    get_vision();
    vector<Point> path = AStar();
    Point next = path.back();
    path.pop_back();
    if(next.x > pos.x) {
      cout << "E";
      pos = pos + DIR_VAL[E];
    } else if(next.x < pos.x) {
      cout << "W";
      pos = pos + DIR_VAL[W];
    } else if(next.y > pos.y) {
      cout << "S";
      pos = pos + DIR_VAL[S];
    } else if(next.y < pos.y) {
      cout << "N";
      pos = pos + DIR_VAL[N];
    }
    
    cout << endl;
  }
}