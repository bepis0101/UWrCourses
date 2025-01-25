// #pragma GCC optimize("Ofast,inline,tracer")
// #pragma GCC optimize("unroll-loops,vpt,split-loops,unswitch-loops,omit-frame-pointer,inline")
// #pragma GCC option("march=native","tune=native","no-zero-upper")            //Enable AVX
// #pragma GCC target("arch=haswell,tune=haswell")
// #pragma GCC target("aes,abm,align-stringops,avx,avx2,bmi,bmi2,crc32,cx16,f16c,fma,fsgsbase,fxsr,hle,ieee-fp,lzcnt,mmx,movbe,mwait,pclmul,popcnt,rdrnd,sahf,sse,sse2,sse3,sse4,sse4.1,sse4.2,ssse3,xsave,xsaveopt")
// #include <x86intrin.h>                                                      //AVX/SSE Extensions


#include <bits/stdc++.h>
#include <chrono>
#include <thread>
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
    int height, width;
    int y_min, y_max, x_min, x_max;
    char my_id, opp_id, main_player;
    int turn;
    vector<string> grid;
    int my_entities = 0, opp_entities = 0;

    State() : my_id(0), opp_id(my_id == '1' ? '0' : '1'), main_player(my_id), grid(vector<string>()), 
          height(grid.size()), width(grid[0].size()),
          y_min(0), y_max(height-1), x_min(0), x_max(width-1),
          turn(0) {}

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
    int id; // Unique ID for this node
    State state;
    int visits;
    double reward;
    vector<int> children; // Store child node IDs
    int parent_id;        // ID of the parent node
    DIR move;

    Node() {
      this->id = -1;
      this->visits = 0;
      this->reward = 0;
      this->parent_id = -1;
      this->move = U;
    }

    Node(const Node& node) {
      this->id = node.id;
      this->visits = node.visits;
      this->reward = node.reward;
      this->parent_id = node.parent_id;
      this->move = node.move;
    }

    Node& operator=(const Node& node) {
      if(this != &node) {
        this->id = node.id;
        this->state = node.state;
        this->visits = node.visits;
        this->reward = node.reward;
        this->children = node.children;
        this->parent_id = node.parent_id;
        this->move = node.move;
      }
      return *this;
    }

    Node(int id, const State& state, int parent_id = -1, DIR move = U)
        : id(id), state(state), visits(0), reward(0.0), parent_id(parent_id), move(move) {}

    bool is_fully_expanded() const {
      return children.size() == 4; // All directions have been explored
    }
};

class MCTS {
public:
    int my_id;
    double exploration_constant;
    vector<Node> node_pool; // Static storage for all nodes
    int node_count;         // Tracks the number of nodes created

    MCTS(char my_id, int max_nodes = 10000, double exploration_constant = 1.414)
        : my_id(my_id), exploration_constant(exploration_constant), node_pool(max_nodes), node_count(0) {}

    double uct_val(const Node& node, const Node& parent) const {
      if (node.visits == 0) {
        return numeric_limits<double>::infinity();
      }
      return (node.reward / node.visits) +
              exploration_constant * sqrt(log(parent.visits) / node.visits);
    }

    double simulate(Node& node) {
        State temp_state = node.state;
        while (!temp_state.is_terminal()) {
          vector<DIR> moves = {U, D, L, R};
          DIR random_move = moves[rand() % moves.size()];
          temp_state.apply_move(random_move);
        }
        return temp_state.eval();
    }

    void backpropagate(int node_id, double reward) {
        while (node_id != -1) {
            Node& node = node_pool[node_id];
            node.visits++;
            node.reward += reward;
            node_id = node.parent_id;
        }
    }

    int best_uct(int node_id) {
        Node& node = node_pool[node_id];
        return *max_element(
            node.children.begin(), node.children.end(),
            [&](int a, int b) {
                return uct_val(node_pool[a], node) < uct_val(node_pool[b], node);
            });
    }

    int expand(int node_id) {
        Node& node = node_pool[node_id];
        vector<DIR> possible_moves = {U, D, L, R};
        for (int child_id : node.children) {
            possible_moves.erase(
                remove(possible_moves.begin(), possible_moves.end(), node_pool[child_id].move),
                possible_moves.end());
        }

        DIR move = possible_moves[rand() % possible_moves.size()];
        State child_state = node.state;
        child_state.apply_move(move);

        node_pool[node_count] = Node(node_count, child_state, node.id, move);
        node.children.push_back(node_count);
        return node_count++;
    }

    int select(int node_id) {
        Node& node = node_pool[node_id];
        while (!node.state.is_terminal() && node.is_fully_expanded()) {
            node_id = best_uct(node.id);
        }

        if (!node.state.is_terminal() && !node.is_fully_expanded()) {
            return expand(node.id);
        }

        return node.id;
    }

    string choose_best_move(State& s, int time_limit = 100) {
        node_count = 0;
        node_pool[node_count] = Node(node_count, s);
        int root_id = node_count++;

        timer.reset();
        while (timer.elapsed() < time_limit) {
            int leaf_id = select(root_id);
            double reward = simulate(node_pool[leaf_id]);
            backpropagate(leaf_id, reward);
        }

        Node& root = node_pool[root_id];
        int best_child_id = *max_element(
            root.children.begin(), root.children.end(),
            [&](int a, int b) { return node_pool[a].visits < node_pool[b].visits; });

        return DIRS[node_pool[best_child_id].move];
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

    string best_move = agent.choose_best_move(state, 90);
    cout << best_move << endl;
  }

  return 0;
}