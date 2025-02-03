// #pragma GCC optimize("Ofast,inline,tracer")
// #pragma GCC optimize("unroll-loops,vpt,split-loops,unswitch-loops,omit-frame-pointer,inline")
// #pragma GCC option("march=native","tune=native","no-zero-upper")            //Enable AVX
// #pragma GCC target("arch=haswell,tune=haswell")
// #pragma GCC target("aes,abm,align-stringops,avx,avx2,bmi,bmi2,crc32,cx16,f16c,fma,fsgsbase,fxsr,hle,ieee-fp,lzcnt,mmx,movbe,mwait,pclmul,popcnt,rdrnd,sahf,sse,sse2,sse3,sse4,sse4.1,sse4.2,ssse3,xsave,xsaveopt")
// #include <x86intrin.h>                                                      //AVX/SSE Extensions

#include <bits/stdc++.h>


using namespace std;
const int WIDTH  = 8;
const int HEIGHT = 8;
const char DEAD_TILE  = 'x';
const char EMPTY_TILE = '-';
const int MAX_TURNS = 200;


enum DIR {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

const string DIRS[4] = {
  "UP", 
  "DOWN", 
  "LEFT", 
  "RIGHT"
};

char grid[HEIGHT][WIDTH];
char main_player;


void grid_preprocessing(vector<string> lines) {
  for(int y = 0; y < lines.size(); y++) {
    for(int x = 0; x < lines[0].size(); x++) {
      grid[y][x] = lines[y][x];
    }
  }
}

double random_uniform() {
  return static_cast<double>(rand()) / (double)RAND_MAX;
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


Timer timer;
int turn;

class State {
public:
  char my_id;
  char opp_id;
  int most_left;
  int most_up;
  int most_right;
  int most_down;
  int my_entities;
  int opp_entities;
  char grid[HEIGHT][WIDTH];
  int turns;

  State() {
    this->my_id = '0';
    this->opp_id = '1';
    this->most_left = 0;
    this->most_up = 0;
    this->most_right = WIDTH-1;
    this->most_down = HEIGHT-1;
    this->my_entities = 32;
    this->opp_entities = 32;
    this->turns = turn;
  }

  State(char my_id) {
    this->my_id = my_id;
    if(my_id == '0') {
      this->opp_id = '1';
    } else {
      this->opp_id = '0';
    }
    this->most_left = 0;
    this->most_up = 0;
    this->most_right = WIDTH-1;
    this->most_down = HEIGHT-1;
    this->my_entities = 32;
    this->opp_entities = 32;
    this->turns = turn;
  }
  
  void swap_players() {
    swap(my_id, opp_id);
    swap(my_entities, opp_entities);
  }

  void calc_entities() {
    my_entities = opp_entities = 0;
    for(int y = most_up; y < most_down; y++) {
      for(int x = most_left; x < most_right; x++) {
        if(grid[y][x] == my_id) {
          my_entities++;
        } else
        if(grid[y][x] == opp_id) {
          opp_entities++;
        }
      }
    }
  }

  int remove_borders_top() {
    int cnt = 0;
    bool empty_rows = true;
    for(int y = 0; y < HEIGHT; y++) {
      for(int x = 0; x < WIDTH; x++) {
        if(grid[y][x] != EMPTY_TILE && grid[y][x] != DEAD_TILE) {
          empty_rows = false;
          break;
        }
      }
      
      if(!empty_rows) break;
      cnt++;
      for(int x = 0; x < WIDTH; x++) {
        grid[y][x] = DEAD_TILE;
      }
    }
    return cnt;
  }

  int remove_borders_bottom() {
    int cnt = 0;
    bool empty_rows = true;
    for(int y = HEIGHT-1; y >= 0; y--) {
      for(int x = 0; x < WIDTH; x++) {
        if(grid[y][x] != EMPTY_TILE && grid[y][x] != DEAD_TILE) {
          empty_rows = false;
          break;
        }
      }
      
      if(!empty_rows) break;
      cnt++;
      for(int x = 0; x < WIDTH; x++) {
        grid[y][x] = DEAD_TILE;
      }
    }
    return cnt;
  }

  int remove_borders_right() {
    int cnt = 0;
    bool empty_cols = true;
    for(int x = WIDTH-1; x >= 0; x--) {
      for(int y = 0; y < HEIGHT; y++) {
        if(grid[y][x] != EMPTY_TILE && grid[y][x] != DEAD_TILE) {
          empty_cols = false;
          break;
        }
      }
      
      if(!empty_cols) break;
      cnt++;
      for(int y = 0; y < HEIGHT; y++) {
        grid[y][x] = DEAD_TILE;
      }
    }
    return cnt;
  }

  int remove_border_left() {
    int cnt = 0;
    bool empty_cols = true;
    for(int x = 0; x < WIDTH; x++) {
      for(int y = 0; y < HEIGHT; y++) {
        if(grid[y][x] != EMPTY_TILE && grid[y][x] != DEAD_TILE) {
          empty_cols = false;
          break;
        }
      }
      
      if(!empty_cols) break;
      cnt++;
      for(int y = 0; y < HEIGHT; y++) {
        grid[y][x] = DEAD_TILE;
      }
    }
    return cnt;
  }

  void apply_up() {
    for(int x = most_left; x <= most_right; x++) {
      char picked = EMPTY_TILE;
      for(int y = most_down; y >= most_up; y--) {
        const char cell = grid[y][x];
        if(picked == EMPTY_TILE && cell == opp_id) continue;
        grid[y][x] = picked;
        picked = cell;
      }
      if(picked == my_entities) my_entities--;
      else if(picked == opp_entities) opp_entities--;
    }
  }
  void apply_down() {
    for(int x = most_left; x <= most_right; x++) {
      char picked = EMPTY_TILE;
      for(int y = most_up; y <= most_down; y++) {
        const char cell = grid[y][x];
        if(picked == EMPTY_TILE && cell == opp_id) continue;
        grid[y][x] = picked;
        picked = cell;
      }
      if(picked == my_entities) my_entities--;
      else if(picked == opp_entities) opp_entities--;
    }
  }
  void apply_right() {
    for(int y = most_up; y <= most_down; y++) {
      char picked = EMPTY_TILE;
      for(int x = most_left; x <= most_right; x++) {
        const char cell = grid[y][x];
        if(picked == EMPTY_TILE && cell == opp_id) continue;
        grid[y][x] = picked;
        picked = cell;
      }
      if(picked == my_id) my_entities--;
      else if(picked == opp_id) opp_entities--;
    }
  }

  void apply_left() {
    for(int y = most_up; y <= most_down; y++) {
      char picked = EMPTY_TILE;
      for(int x = most_right; x >= most_left; x--) {
        const char cell = grid[y][x];
        if(picked == EMPTY_TILE && cell == opp_id) continue;
        grid[y][x] = picked;
        picked = cell;
      }
      if(picked == my_id) my_entities--;
      else if(picked == opp_id) opp_entities--;
    }
  }

  void apply_move(DIR mov) {
    switch(mov) {
      case UP:
        apply_up();
        break;
      case DOWN:
        apply_down();
        break;
      case RIGHT:
        apply_right();
        break;
      case LEFT:
        apply_left();
        break;
    }

    most_up = remove_borders_top();
    most_left = remove_border_left();
    most_down = HEIGHT-remove_borders_bottom()-1;
    most_right = WIDTH-remove_borders_right()-1;
    turns++;

    swap_players();
  }

  int eval() { 
    if(main_player != my_id) {
      swap_players();
    }

    if(my_entities == 0 && opp_entities != 0) return -(WIDTH*HEIGHT);
    else if(opp_entities == 0) return WIDTH*HEIGHT;
    else return my_entities - opp_entities;
  }

  bool is_terminal() {
    return turns >= MAX_TURNS || my_entities == 0 || opp_entities == 0;
  }

};

void debug_grid(const State& s) {
  for(int y = 0; y < HEIGHT; y++) {
    for(int x = 0; x < WIDTH; x++) {
      cerr << s.grid[y][x];
    }
    cerr << '\n';
  }
  cerr << '\n';
}

DIR get_random_dir() {
  return static_cast<DIR>(rand()%4);
}

int sim(State& state) {
  int cnt = 0;
  while(!state.is_terminal()) {
    DIR dir = get_random_dir();
    state.apply_move(dir);
    if(cnt < 10 && turn > 20 && false) {
      cerr << "DIRECTION SIMULATED: " << DIRS[dir] << '\n';
      cerr << "BORDERS: " << state.most_up << ' ' << state.most_down << ' ' << state.most_left << ' ' << state.most_right << '\n';
      cerr << "ENTITIES: " << state.my_entities << ' ' << state.opp_entities << '\n';
      debug_grid(state);
    }
    cnt++;
  }
  return state.eval();
}

string flatMC(const State& state, int time_limit = 100) {
  double rewards[4] = {0.0};
  int counts[4] = {0};
  timer.reset();
  while(timer.elapsed() < time_limit) {
    State cp_state = state;
    DIR dir = get_random_dir();
    cp_state.apply_move(dir);
    int reward = sim(cp_state);
    rewards[dir] += reward;
    counts[dir]++;
  }
  cerr << '\n';

  double best = -1e9;
  int best_dir = 0;

  for(int i = 0; i < 4; i++) {
    if(counts[i] > 0) {
      double avg = rewards[i] / counts[i];
      if(avg > best) {
        best = avg;
        best_dir = i;
      }
      cerr << "\nfor " << DIRS[i] << " avg: " << avg << " count: " << counts[i] << " reward: " << rewards[i] << '\n';
    }
  }



  return DIRS[best_dir];
}


int main() {
  srand(time(0));

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  char my_id; // Your id, 0 or 1
  cin >> my_id; cin.ignore();
  main_player = my_id;
  int height; // height of the grid
  cin >> height; cin.ignore();
  int width; // width of the grid
  cin >> width; cin.ignore();

  State state(my_id);
  // game loop
  while (1) {
    state.turns = turn;
    
    for (int i = 0; i < HEIGHT; i++) {
      for(int j = 0; j < WIDTH; j++) {
        cin >> state.grid[i][j];
      }
    }
    state.calc_entities();
    // cerr << state.my_entities << ' ' << state.opp_entities << ' ' << state.turns << '\n';
    string best_move = flatMC(state);
    debug_grid(state);
    cout << best_move << endl;

    turn += 2;
  }

  return 0;
}