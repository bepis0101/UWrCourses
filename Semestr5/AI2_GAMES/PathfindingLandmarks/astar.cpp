#include <bits/stdc++.h>
using namespace std;


pair<pair<int, int>, float> moves[8] = {
  {{0, -1}, 1.},
  {{1, -1}, M_SQRT2},
  {{1, 0}, 1.},
  {{1, 1}, M_SQRT2},
  {{0, 1}, 1.},
  {{-1, 1}, M_SQRT2},
  {{-1, 0}, 1.},
  {{-1, -1}, M_SQRT2}
};

const int MAX_WH = 240;

class Timer {
public:
    chrono::time_point<chrono::high_resolution_clock> start_time;
    Timer() : start_time(chrono::high_resolution_clock::now()) {}

    void reset() {
      start_time = chrono::high_resolution_clock::now();
    }

    int64_t elapsed() {
      return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count();
    }
};

char board[MAX_WH][MAX_WH];
int WIDTH;
int HEIGHT;

void parse_input(vector<string> b, int width, int height) {
  WIDTH = width;
  HEIGHT = height;
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      board[y][x] = b[y][x];
    }
  }
}

class Landmark {
public:
  int x;
  int y;
  float distances[MAX_WH][MAX_WH];
  Landmark() {
    this->x = 0;
    this->y = 0;
  };
  Landmark(int x, int y) {
    this->x = x;
    this->y = y;
    this->calc_dists();
  }
  void calc_dists() {
    for(int y = 0; y < HEIGHT; y++) {
      for(int x = 0; x < WIDTH; x++) {
        distances[y][x] = FLT_MAX;
      }
    }
    bool visited[HEIGHT][WIDTH] = {{false}};
    visited[this->y][this->x] = true;
    distances[this->y][this->x] = 0.;
    queue<pair<int, int>> q;
    q.push({this->x, this->y});
    while(!q.empty()) {
      pair<int, int> node = q.front();
      visited[node.second][node.first] = true;
      q.pop();
      for(int i = 0; i < 8; i++) {
        auto move = moves[i];
        int x = node.first+move.first.first;
        int y = node.second+move.first.second;
        if(board[y][x] == '.' and !visited[y][x]) {
          q.push({x, y});
          distances[y][x] = distances[node.second][node.first] + move.second;
        }
      }
    }
  }
  void print_dists() {
    for(int y = 0; y < HEIGHT; y++) {
      for(int x = 0; x < WIDTH; x++) {
        cerr << distances[y][x] << ' ';
      }
      cerr << '\n';
    }
  }
};

class Node {
public:
  float heura;
  float dist;
  int x;
  int y;
  int vis_cnt;
  Node() {
    this->heura   = 0.;
    this->dist    = 0.;
    this->x       = 0;
    this->y       = 0;
    this->vis_cnt = 0;
  }
  Node(float heura, float dist, int x, int y, int vis_cnt) {
    this->heura = heura;
    this->dist = dist;
    this->vis_cnt = vis_cnt;
    this->x = x;
    this->y = y;
  }
};

class Map {
  int x_start;
  int y_start;
  int x_end;
  int y_end;
  int num_landmarks;
public:
  vector<Landmark> ls;
  Map() {}
  Map(int x_start, int y_start, int x_end, int y_end, int num_landmarks) {
    this->x_start = x_start;
    this->x_end = x_end;
    this->y_start = y_start;
    this->y_end = y_end;
    this->num_landmarks = num_landmarks;
  }

  inline float get_best(int x_start, int y_start, int x_end, int y_end) {
    float res = FLT_MIN;

    for(int i = 0; i < ls.size(); i++) {
      if(ls[i].distances[y_start][x_start] != FLT_MAX and ls[i].distances[y_end][x_end] != FLT_MAX) {
        res = max(abs(ls[i].distances[y_start][x_start] - ls[i].distances[y_end][x_end]), res);
      }
    }

    return res;
  }

  float AStar() {
    bool visited[HEIGHT][WIDTH];
    int vis_num = 1;
    auto lam = [](Node& a, Node& b) {
      return a.heura < b.heura;
    };
    priority_queue<Node, vector<Node>, decltype(lam)> pq(lam);
    pq.push(Node(get_best(x_start, y_start, x_end, y_end), 0, x_start, y_start, 1));
    while(!pq.empty()) {
      auto node = pq.top();
      pq.pop();
      if(node.x == x_end and node.y == y_end) {
        return (float)node.vis_cnt / (float)vis_num;
      }
      for(int i = 0; i < 8; i++) {
        auto move = moves[i];
        int x = node.x+move.first.first;
        int y = node.y+move.first.second;
        if(!visited[y][x] and board[y][x] == '.') {
          pq.push(Node(get_best(x, y, x_end, y_end), node.dist+move.second, x, y, node.vis_cnt+1));
          visited[y][x] = true;
          vis_num++;
        }
      }
    }
    return 0.0;
  }

  void generate_landmarks() {
    ls.clear();
    for(int i = 0; i < num_landmarks; i++) {
      int x = rand() % (WIDTH-2)+1;
      int y = rand() % (HEIGHT-2)+1;
      ls.push_back(Landmark(x, y));
    }
  }
  void regenerate() {
    x_start = rand() % (WIDTH-2)+1, y_start = rand() % (HEIGHT-2)+1, x_end = rand() % (WIDTH-2)+1, y_end = rand() % (HEIGHT-2)+1;
  }
};

class Solution {
  Map best;
  int num_landmarks;
public:
  Solution(int num_landmarks) {
    this->num_landmarks = num_landmarks;
  }
  vector<Landmark> sim() {
    float best_avg = 0.0;
    Map curr = Map(rand() % (WIDTH-2)+1, rand() % (HEIGHT-2)+1, rand() % (WIDTH-2)+1, rand() % (HEIGHT-2)+1, num_landmarks);
    best = curr;
    Timer total;
    while(total.elapsed() < 9500) {
      float avg = 0.;
      int reruns = 0;
      Timer t;
      curr.generate_landmarks();
      while(t.elapsed() < 75) {
        avg += curr.AStar();
        reruns++;
        curr.regenerate();
      }
      if(avg / (float)reruns > best_avg) {
        best = curr;
        best_avg = avg / (float)reruns;
      }
      cerr << "check\n";
    }
    return best.ls;
  }
};


int main()
{
    srand(time(NULL));
    int landmarks_num; // Number of landmarks to place
    float efficiency; // Minimal average efficiency required to pass the test
    cin >> landmarks_num >> efficiency; cin.ignore();
    int width; // Width of the map
    int height; // Height of the map
    cin >> width >> height; cin.ignore();
    vector<string> b(height);
    for (int i = 0; i < height; i++) {
        string row; // A single row of the map consisting of passable terrain ('.') and walls ('#')
        cin >> row; cin.ignore();
        b[i] = row;
    }
    parse_input(b, width, height);
    Solution s = Solution(landmarks_num);
    auto res = s.sim();
    for (int i = 0; i < landmarks_num; i++) {
      cout << res[i].x << ' ' << res[i].y << endl;
    }
}