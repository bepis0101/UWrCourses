// #pragma GCC optimize("Ofast,inline,tracer")
// #pragma GCC optimize("unroll-loops,vpt,split-loops,unswitch-loops,omit-frame-pointer,inline")
// #pragma GCC option("march=native","tune=native","no-zero-upper")            //Enable AVX
// #pragma GCC target("arch=haswell,tune=haswell")
// #pragma GCC target("aes,abm,align-stringops,avx,avx2,bmi,bmi2,crc32,cx16,f16c,fma,fsgsbase,fxsr,hle,ieee-fp,lzcnt,mmx,movbe,mwait,pclmul,popcnt,rdrnd,sahf,sse,sse2,sse3,sse4,sse4.1,sse4.2,ssse3,xsave,xsaveopt")
// #include <x86intrin.h>                                                      //AVX/SSE Extensions


#include <bits/stdc++.h>
#include <chrono>
using namespace std;

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


enum DIR {U, D, L, R};
const string DIRS[] = {"UP", "DOWN", "LEFT", "RIGHT"};

const char EMPTY_TILE = '-', DEAD_TILE = 'x';
const int MAX_TURNS = 200;

Timer timer;

class State {
public:
    const int height, width;
    int y_min, y_max, x_min, x_max;
    char my_id, opp_id, main_player;
    int turn;
    vector<string> grid;
    int my_entities = 0, opp_entities = 0;

    State(char my_id, const vector<string>& grid)
        : my_id(my_id), opp_id(my_id == '1' ? '0' : '1'), main_player(my_id), grid(grid), 
          height(grid.size()), width(grid[0].size()),
          y_min(0), y_max(height-1), x_min(0), x_max(width-1),
          turn(0) {
    }

    void recalc_entities() {
      my_entities = opp_entities = 0;
      for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
          if(grid[y][x] == my_id) {
            my_entities++;
          } else
          if(grid[y][x] == opp_id) {
            opp_entities++;
          }
        }
      }
    }

    void swap_players() {
        swap(my_id, opp_id);
        swap(my_entities, opp_entities);
    }

    int remove_borders_up() {
      int cnt_removed = 0;
      bool to_erase = true;
      for(int y = y_min; y <= y_max; y++) {
        for(int x = x_min; x <= x_max; x++) {
          if(grid[y][x] != EMPTY_TILE) {
            to_erase = false;
            break;
          }
        }
        
        if(!to_erase) break;
        cnt_removed++;
        for(int x = x_min; x <= x_max; x++) {
          grid[y][x] = DEAD_TILE;
        }
      }
      return cnt_removed;
    }

    int remove_borders_down() {
      int cnt_removed = 0;
      bool to_erase = true;
      for(int y = y_max; y >= y_min; y--) {
        for(int x = x_min; x <= x_max; x++) {
          if(grid[y][x] != EMPTY_TILE) {
            to_erase = false;
            break;
          }
        }
        if(!to_erase) break;
        cnt_removed++;
        for(int x = x_min; x <= x_max; x++) {
          grid[y][x] = DEAD_TILE;
        }
      }
      return cnt_removed;
    }

    int remove_borders_left() {
      int cnt_removed = 0;
      bool to_erase = true;
      for(int x = x_min; x <= x_max; x++) {
        for(int y = y_min; y <= y_max; y++) {
          if(grid[y][x] != EMPTY_TILE) {
            to_erase = false;
            break;
          }
        }
        if(!to_erase) break;
        cnt_removed++;
        for(int y = y_min; y <= y_max; y++) {
          grid[y][x] = DEAD_TILE;
        }
      }
      return cnt_removed;
    }
    
    int remove_borders_right() {
      int cnt_removed = 0;
      bool to_erase = true;
      for(int x = x_max; x >= x_min; x--) {
        for(int y = y_min; y <= y_max; y++) {
          if(grid[y][x] != EMPTY_TILE) {
            to_erase = false;
            break;
          }
        }
        if(!to_erase) break;
        cnt_removed++;
        for(int y = y_min; y <= y_max; y++) {
          grid[y][x] = DEAD_TILE;
        }
      }
      return cnt_removed;
    }


    void apply_move(const DIR dir) {
        // cerr << "Applying move " << DIRS[dir] << " with " << my_id << '\n';

      if(dir == U || dir == D) {
        for(int col = x_min; col <= x_max; col++) {
          char picked = EMPTY_TILE;

          int row_dir = (dir == U ? -1 : 1);
          int row = (dir == U ? y_max : y_min);

          for(; row >= y_min && row <= y_max; row += row_dir) {
              const char cell = grid[row][col];

              if(picked == EMPTY_TILE && cell == opp_id) {
                continue;
              }

              grid[row][col] = picked;
              picked = cell;
          }

          if(picked == my_id) my_entities--;
          else if(picked == opp_id) opp_entities--;
        }
      } else {
        for(int row = y_min; row <= y_max; row++) {
          char picked = EMPTY_TILE;

          int col_dir = (dir == L ? -1 : 1);
          int col = (dir == L ? x_max : x_min);

          for(; col >= x_min && col <= x_max; col += col_dir) {
              const char cell = grid[row][col];

              if(picked == EMPTY_TILE && cell == opp_id) {
                continue;
              }

              grid[row][col] = picked;
              picked = cell;
          }

          // piece that falls off the board
          if(picked == my_id) my_entities--;
          else if(picked == opp_id) opp_entities--;
        }
      }

      // cerr << "row col from to before: " << y_min << ' ' << y_max << ' ' << x_min << ' ' << x_max << '\n';
      y_min += remove_borders_up();
      y_max -= remove_borders_down();
      x_min += remove_borders_left();
      x_max -= remove_borders_right();
      // cerr << "row col from to after: " << y_min << ' ' << y_max << ' ' << x_min << ' ' << x_max << '\n';

      turn++;
      swap_players();
    }

    int eval() {
        if(main_player != my_id) {
          swap_players();
        }

        if(my_entities == 0 && opp_entities != 0) {
          return -(height * width);
        } else if(opp_entities == 0) {
          return (height * width);
        } else {
          // return (my_entities > opp_entities ? 1 : (my_entities < opp_entities ? -1 : 0));
          return my_entities - opp_entities;
        }
    }

    bool is_terminal() {
      return turn >= MAX_TURNS || my_entities == 0 || opp_entities == 0;
    }


    void debug_grid() {
      for(const auto& row : grid) {
        cerr << row << '\n';
      }
    }

    friend ostream& operator<<(ostream& os, const State& state) {
      os << "Main player: " << state.main_player << ", My id: " << state.my_id << ", Opp id: " << state.opp_id << '\n';
      os << "My entities: " << state.my_entities << ", Opp entities: " << state.opp_entities << '\n';
      for(const auto& row : state.grid) {
        os << row << '\n';
      }
      return os;
    }
};

class Node {
public:
  State state;
  int visits;
  double reward;
  vector<Node*> children;
  Node* parent;
  DIR move;

  Node(State state, Node* parent = nullptr, DIR move = U) : 
    state(state), visits(0), reward(0.0), parent(parent), move(move) {}

  ~Node() {
    for(Node* child : children) {
      delete child;
    }
  }

  bool is_fully_expanded() const {
    return children.size() == 4;
  }
};


class MCTS {
public:
  int my_id;
  double exploration_constant;
  MCTS(char my_id, int max_iterations = 200, double exploration_constant = 1.414) :
    my_id(my_id), exploration_constant(exploration_constant) {}

  double uct_val(Node* node) const {
    if(node->visits == 0) {
      return numeric_limits<double>::infinity();
    }
    return (node->reward / node->visits) + exploration_constant * sqrt(log(node->parent->visits) / node->visits);
  }

  double simulate(Node* node) {
    State temp_state = node->state;
    while (!temp_state.is_terminal()) {
      vector<DIR> moves = {U, D, L, R};
      DIR random_move = moves[rand() % moves.size()];
      temp_state.apply_move(random_move);
    }
    return temp_state.eval();
  }

  void backpropagate(Node* node, double reward) {
    while (node != nullptr) {
      node->visits++;
      node->reward += reward;
      node = node->parent;
    }
  }

  Node* best_uct(Node* node) {
    return *max_element(
      node->children.begin(), node->children.end(),
      [this](Node* a, Node* b) {
          double uct_a = uct_val(a);
          double uct_b = uct_val(b);
          return uct_a < uct_b;
      });
  }

  Node* expand(Node* node) {
    vector<DIR> possible_moves = {U, D, L, R};
    for (Node* child : node->children) {
      possible_moves.erase(remove(possible_moves.begin(), possible_moves.end(), child->move), possible_moves.end());
    }

    DIR move = possible_moves[rand() % possible_moves.size()];
    State child_state = node->state;
    child_state.apply_move(move);

    Node* child = new Node(child_state, node, move);
    node->children.push_back(child);
    return child;
  }

  Node* select(Node* node) {
    while (!node->state.is_terminal() && node->is_fully_expanded()) {
      node = best_uct(node);
    }

    if (!node->state.is_terminal() && !node->is_fully_expanded()) {
      return expand(node);
    }

    return node;
  }

  string choose_best_move(State& s, int time_limit = 100) {
    Node* root = new Node(s);
    timer.reset();
    while(timer.elapsed() < time_limit) {
      Node* leaf = select(root);
      double reward = simulate(leaf);
      backpropagate(leaf, reward);
    }
    
    Node* best_child = *max_element(root->children.begin(), root->children.end(), 
                                    [](Node* a, Node* b) { return a->visits < b->visits; });
    string best_move = DIRS[best_child->move];
    delete root;
    return best_move;
  }

};



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  srand(time(0));

  char my_id;
  cin >> my_id; cin.ignore();
  int height, width;
  cin >> height >> width; cin.ignore();

  State state(my_id, vector<string>(height, string(width, ' ')));
  MCTS agent(my_id);

  while(true) {
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        cin >> state.grid[i][j];
      }
    }
    state.recalc_entities();

    string best_move = agent.choose_best_move(state);
    cout << best_move << endl;
  }

  return 0;
}