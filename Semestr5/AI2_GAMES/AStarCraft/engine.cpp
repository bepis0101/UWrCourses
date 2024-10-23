#include <bits/stdc++.h>
using namespace std;

const int ROWS = 10;
const int COLS = 19;

map<char, short> DIRS = {{'L', 0}, {'R', 1}, {'U', 2}, {'D', 3}};
char DIRS_REV[4] = {'L', 'R', 'U', 'D'};

struct Position {
  int x;
  int y;
};

map<char, Position> Direction = {{'L', {-1, 0}}, {'R', {1, 0}}, {'U', {0, -1}}, {'D', {0, 1}}};


int myModulo(int x, int p) {
  return (x+p)%p;
}

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
  Robot(int x, int y) {
    this->isActive  = true;
    Position pos    = {x, y};
    this->pos       = pos;
    this->direction = 'R';

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


class State {
private:
  char board[ROWS][COLS];
  vector<Robot> robots;
  int score;
  vector<pair<Position, char>> genArrows;
public:
  State(vector<Robot> robots, char board[ROWS][COLS]) {
    this-> robots = robots;
    this->score = 0;
    for(int y = 0; y < ROWS; y++) {
      for(int x = 0; x < COLS; x++) {
        this->board[y][x] = board[y][x];
      }
    }
  }
  
  bool checkIfAnyRobotsAreAlive() {
    for(auto &r : robots) {
      if(r.isActive) return true;
    }
    return false;
  }

  int getScore() {
    return score;
  }

  void makeMoves() {
    for(auto &r : robots) {
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
  void generateValidArrows() {
    int freeSpaces = 0;
    for(int y = 0; y < ROWS; y++) {
      for(int x = 0; x < COLS; x++) {
        if(board[y][x] == '.') {
          freeSpaces++;      
        }
      }
    }
    int random = rand() % freeSpaces;
    float prob = (float)random / (float)freeSpaces;
    default_random_engine gen;
    for(int y = 0; y < ROWS; y++) {
      for(int x = 0; x < COLS; x++) {
        if(board[y][x] == '.') {
          uniform_real_distribution<float> dist(0.0, 1.0);
          float temp = dist(gen);
          if(temp <= prob) {
            random = rand() % 4;
            genArrows.push_back({{x, y}, DIRS_REV[random]});
            board[y][x] = DIRS_REV[random];
          }
        }
      }
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


int main() {

  srand(time(NULL));
  char board[ROWS][COLS];
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
    robots[i] = Robot(x, y);
  }

  Timer t;
  State s = State(robots, board);
  State maks = s;
  int iterations = 0;

  while(t.elapsed() <= 900) {
    iterations++;
    while(s.checkIfAnyRobotsAreAlive()) {
      s.makeMoves();
    }
    if(s.getScore() > maks.getScore()) {
      maks = s;
    }
    s = State(robots, board);
    s.generateValidArrows();
  }
  cerr << maks.getScore();
  
  maks.printArrows();

}