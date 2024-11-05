#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,inline,tracer")
#pragma GCC optimize("unroll-loops,vpt,split-loops,unswitch-loops")
#pragma GCC target("arch=haswell,tune=haswell")
#pragma GCC target("aes,abm,align-stringops,avx,avx2,bmi,bmi2,crc32,cx16,f16c,fma,fsgsbase,fxsr,hle,ieee-fp,lzcnt,mmx,movbe,mwait,pclmul,popcnt,rdrnd,sahf,sse,sse2,sse3,sse4,sse4.1,sse4.2,ssse3,xsave,xsaveopt")

using namespace std;

const int ROWS = 10;
const int COLS = 19;

const int TIME_LIMIT = 750;
const double START_TEMP = 30.0;
const double END_TEMP = 0.0000001;
const int N = 400;

map<char, short> DIRS = {{'L', 0}, {'R', 1}, {'U', 2}, {'D', 3}};
char DIRS_REV[4] = {'L', 'R', 'U', 'D'};

struct Position {
  int x = -1;
  int y = -1;
};
bool operator==(const Position& lhs, const Position& rhs) {
  return lhs.x == rhs.x && rhs.y == lhs.y;
}

map<char, Position> Direction = {{'L', {-1, 0}}, {'R', {1, 0}}, {'U', {0, -1}}, {'D', {0, 1}}};


int myModulo(int x, int p) {
  return (x+p)%p;
}

struct hashPos {
  size_t operator() (const Position& pos) const noexcept {
    size_t x = hash<int>{}(pos.x);
    size_t y = hash<int>{}(pos.y);
    return x ^ (y << 1);
  }
};

class Robot {
private:
  Position pos;
  char direction;
  bool visited[ROWS][COLS][4];
public:
  bool isActive;
  Robot() {
    this->isActive = false;
    this->pos = {-1, -1};
    this->direction = 'R';
  }
  Robot(int x, int y, char direction) {
    this->isActive  = true;
    Position pos    = {x, y};
    this->pos       = pos;
    this->direction = direction;

    for(int k = 0; k < 4; k++) {
      for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
          visited[i][j][k] = false;
        }
      }
    }

  }

  bool isVisited() {
    return visited[pos.y][pos.x][DIRS[direction]];
  }

  void addToVisited() {
    visited[pos.y][pos.x][DIRS[direction]] = true;
  }

  Position getPosition() {
    return pos;
  }

  void changeDirection(char dir) {
    direction = dir;
  }

  void moveBot() {
    pos.x += Direction[direction].x;
    pos.y += Direction[direction].y;
    pos.x = myModulo(pos.x, COLS);
    pos.y = myModulo(pos.y, ROWS);
  }
};

bool isArrow(char c) {
  if(c == 'L' or c == 'R' or c == 'U' or c == 'D') return true;
  return false;
}

class State {
private:
  vector<Robot> robots;
  int score;
public:
  char board[ROWS][COLS];
  vector<pair<Position, char>> genArrows;
  unordered_set<Position, hashPos> freePositions;
  State(vector<Robot> robots, char board[ROWS][COLS]) {
    this-> robots = robots;
    this->score = 0;
    for(int y = 0; y < ROWS; y++) {
      for(int x = 0; x < COLS; x++) {
        this->board[y][x] = board[y][x];
        if(board[y][x] == '.') {
          freePositions.insert({x, y});
        }
      }
    }
  }
  
  bool checkIfAnyRobotsAreAlive(vector<Robot> robotsCopy) {
    for(auto &r : robotsCopy) {
      if(r.isActive) return true;
    }
    return false;
  }

  int getScore() {
    return score;
  }

  void makeMoves() {
    vector<Robot> robotsCopy = robots;
    while(checkIfAnyRobotsAreAlive(robotsCopy)) {
      for(auto &r : robotsCopy) {
        r.addToVisited();

        Position robotPos = r.getPosition();

        switch(board[robotPos.y][robotPos.x]) {
          case 'L':
            r.changeDirection('L');
            break;
          case 'R':
            r.changeDirection('R');
            break;
          case 'U':
            r.changeDirection('U');
            break;
          case 'D':
            r.changeDirection('D');
            break;
          case '#':
            r.isActive = false;
            break;
          default:
            break;
        }
        if(r.isActive) score++;
        else continue;
        r.moveBot();
        // if we double the position with direction then robot dies
        if(r.isVisited()) {
          r.isActive = false;
          continue;
        }
        //mark the position that robot just visited
        r.addToVisited();
      }
    }
  }

  
  bool checkIfArrowIsCorrect(Position pos, char arrow) {
    char arrowIndicator = board[myModulo(pos.y+Direction[arrow].y, ROWS)][myModulo(pos.x+Direction[arrow].x, COLS)];
    if(arrowIndicator == '#') {
      return false;
    }
    if(isArrow(arrowIndicator)) {
      if(Direction[arrow].x+Direction[arrowIndicator].x == 0 and Direction[arrow].y == Direction[arrowIndicator].y == 0) {
        return false;
      } 
    }
    return true;
  }
  void generateValidArrows() {
    vector<Position> deleted;
    int random = rand() % freePositions.size();
    float prob = (float)random / (float)freePositions.size();
    default_random_engine gen;
    for(auto pos : freePositions) {
      uniform_real_distribution<float> dist(0.0, 1.0);
      float temp = dist(gen);
      if(temp <= prob) {
        random = rand() % 4;
        char arrow = DIRS_REV[random];
        if(checkIfArrowIsCorrect(pos, arrow)) {
          genArrows.push_back({pos, arrow});
          board[pos.y][pos.x] = arrow;
          deleted.push_back(pos);
        } else {
          continue;
        }
      }
    }
    for(auto pos : deleted) {
      freePositions.erase(pos);
    }
  }

  void printArrows() {
    for(auto arrow : genArrows) {
      cout << arrow.first.x << ' ' << arrow.first.y << ' ' << arrow.second << ' ';
    }
    cout << endl;
  }

  void debug() {
    cerr << "BOARD:\n";
    for(int y = 0; y < ROWS; y++) {
      for(int x = 0; x < COLS; x++) {
        bool check = false;
        for(auto &r : robots) {
          if(r.getPosition().x == x and r.getPosition().y == y) {
            check = true;
            cerr << "r ";
            break;
          }
        }
        if(!check) cerr << board[y][x] << ' '; 
      }
      cerr << '\n';
    }
  }

};

State mutate(State& current) {
  // we have 3 types of mutations
  // 0. adding an arrow
  // 1. deleting an arrow
  // 2. changing the direction of an arrow
  int random = rand() % 3;
  State res = current;
  vector<Position> temp;
  copy(current.freePositions.begin(), current.freePositions.end(), back_inserter(temp));
  switch(random) {
    case 0:
      if(temp.size() > 0) {
        int idx = rand() % temp.size();
        char randomArrow = DIRS_REV[rand() % 4];
        if(current.checkIfArrowIsCorrect(temp[idx], randomArrow)) {
          res.genArrows.push_back({temp[idx], randomArrow});
          res.freePositions.erase(temp[idx]);
          res.board[temp[idx].y][temp[idx].x] = randomArrow;
        } else {
          return mutate(current);
        }
      } else {
        return mutate(current);
      }
      break;
    case 1:
      if(current.genArrows.size() > 0) {
        int idx = rand() % current.genArrows.size();
        res.freePositions.insert(current.genArrows[idx].first);
        res.board[current.genArrows[idx].first.y][current.genArrows[idx].first.x] = '.';
        res.genArrows.erase(res.genArrows.begin() + idx);
      } else {
        return mutate(current);
      }
      break;
    case 2:
      if(current.genArrows.size() > 0) {
        int idx = rand() % current.genArrows.size();
        char randomArrow = DIRS_REV[rand() % 4];
        while(randomArrow == res.board[current.genArrows[idx].first.y][current.genArrows[idx].first.x]) {
          randomArrow = DIRS_REV[rand() % 4];
        }
        res.board[current.genArrows[idx].first.y][current.genArrows[idx].first.x] = randomArrow;
        res.genArrows[idx].second = randomArrow;
      } else {
        return mutate(current);
      }
      break;
  }
  return res;
}

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

char board[ROWS][COLS];

vector<Robot> parseInput() {
  for (int i = 0; i < 10; i++) {
    string line;
    getline(cin, line);
    for(int j = 0; j < line.size(); j++) {
      board[i][j] = line[j];
    }
  }
  int robot_count;
  cin >> robot_count; cin.ignore();
  vector<Robot> robots(robot_count);
  for (int i = 0; i < robot_count; i++) {
    int x;
    int y;
    string direction;
    cin >> x >> y >> direction; cin.ignore();
    robots[i] = Robot(x, y, direction[0]);
  }
  return robots;
}
double randomm(double lo = 0.0, double hi = 1.0) {
  default_random_engine gen;
  uniform_real_distribution<double> dist(lo, hi);
  return dist(gen);
}

int main() {
  srand(time(NULL));
  auto robots = parseInput();
  State init = State(robots, board);
  init.generateValidArrows();
  
  Timer t;
  State curr = init;
  State maks = curr;
  maks.makeMoves();

  while(true) {
    if(t.elapsed() > TIME_LIMIT) break;
    double timeFrac = (double)t.elapsed() / (double)TIME_LIMIT;
    double temp = START_TEMP * pow(END_TEMP/START_TEMP, timeFrac);
    for(int i = 0; i < N; i++) {
      State currCopy = curr;
      State candidate = mutate(curr);
      State candidateCopy = candidate;
      candidateCopy.makeMoves();
      currCopy.makeMoves();
      int diff = candidateCopy.getScore() - currCopy.getScore();
      if(diff > 0 || randomm() < exp((double)diff / temp)) {
        curr = candidate;
        if(candidateCopy.getScore() > maks.getScore()) {
          maks = candidateCopy;
        }
      }    
    }
  }
  maks.printArrows();
}