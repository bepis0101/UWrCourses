#include <bits/stdc++.h>

using namespace std;

const int BLACK = 1;
const int WHITE = -1;

const int L = 8;
const pair<int, int> directions[8] = {
  {-1, -1},
  {-1, 0},
  {-1, 1},
  {0, -1},
  {0, 1},
  {1, -1},
  {1, 0},
  {1, 1}
};

class State {
  public:
  int myColor;
  int color;
  int board[L][L];
  
  State() {
    for(int i = 0; i < L; i++) {
      for(int j = 0; j < L; j++) {
        board[i][j] = 0;
      }
    }
    board[3][3] = WHITE;
    board[4][4] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
  }

  State(const State& other) {
    this->myColor = other.myColor;
    this->color = other.color;
    for(int i = 0; i < L; i++) {
      for(int j = 0; j < L; j++) {
        this->board[i][j] = other.board[i][j];
      }
    }
  }


  // -1 or 1 if win 0 if is not end 5 if draw
  int isEnd() {
    int blacks = 0, whites = 0;
    if(generateMoves(WHITE).empty() || generateMoves(BLACK).empty()) {
      return 0;
    }
    for(int y = 0; y < L; y++) {
      for(int x = 0; x < L; x++) {
        if(board[y][x] == WHITE) whites++;
        else if(board[y][x] == BLACK) blacks++;
      }
    }
    if(blacks == whites) {
      return 5;
    } else if(blacks < whites) {
      return WHITE;
    } else {
      return BLACK;
    }
  }
  
  bool makeMove(int color, int x, int y) {
    bool success = false;
    for(auto dir : directions) {
      auto [dx, dy] = dir;
      int nx = x + dx; 
      int ny = y + dy;
      if(isCorrect(color, x, y, dir)) {
        while(nx > 0 && nx < 8 && ny > 0 && ny < 8) {
          if(board[ny][nx] == color) break;
          if(board[ny][nx] == -color) board[ny][nx] = color;
          nx += dx, ny += dy;
        }
        success = true;
      }
    }
    if(success) board[y][x] = color;
    return success;
  }
  
  vector<pair<int, int>> generateMoves(int color) {
    vector<pair<int, int>> res;
    for(int y = 0; y < L; y++) {
      for(int x = 0; x < L; x++) {
        for(auto dir : directions) {
          if(isCorrect(color, x, y, dir)) {
            res.push_back({x, y});
          }
        }
      }
    }
    return res;
  }
  
  bool isCorrect(int color, int x, int y, pair<int, int> dir) {
    if(board[y][x] != 0) return false;
    auto [dx, dy] = dir;
    int nx = x + dx, ny = y + dy;
    if(nx < 0 || ny < 0 || nx >= L || ny >= L || board[ny][nx] != -color) return false;
    while(nx > 0 && nx < 8 && ny > 0 && ny < 8) {
      if(board[ny][nx] == color) {
        return true;
      }
      nx += dx, ny += dy;
    }
    
    return false;
  }
  
  void changeColor() {
    color = -color;
  }
  
  void printBoard() {
    for(int y = 0; y < L; y++) {
      for(int x = 0; x < L; x++) {
        fprintf(stderr, "%2d ", board[y][x]);
      }
      fprintf(stderr, "\n");
    }
  }
};

void printMoves(State& s) {
  auto moves = s.generateMoves(s.myColor);
  for(auto move : moves) {
    cout << "{" << move.first << ", " << move.second << "}, ";
  }
  cout << "\n";
}

void printMoves(vector<pair<int, int>> moves) {
  for(auto move : moves) {
    cerr << "{" << move.first << ", " << move.second << "}, ";
  }
  cerr << "\n";
}

class Agent {  
  const int board_weights[L][L] = {
    {100, -20, 10,  5,  5, 10, -20, 100},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {10,  -2,  -1, -1, -1, -1,  -2,  10},
    {5,   -2,  -1, -1, -1, -1,  -2,   5},
    {5,   -2,  -1, -1, -1, -1,  -2,   5},
    {10,  -2,  -1, -1, -1, -1,  -2,  10},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {100, -20, 10,  5,  5, 10, -20, 100}
  };

public:
  int evaluate(const State& s) const {
    int score = 0;
    for(int y = 0; y < L; y++) {
      for(int x = 0; x < L; x++) {
        if(s.board[y][x] == s.myColor) {
          score += board_weights[y][x];
        } else if(s.board[y][x] == -s.myColor) {
          score -= board_weights[y][x];
        }
      }
    }
    return score;
  }

  int alphaBeta(State& s, int depth, int alpha, int beta, bool maximizing) {
    if (depth == 0 || s.isEnd()) {
      return evaluate(s);
    }

    vector<pair<int, int>> moves = s.generateMoves(s.color);
    if (moves.empty()) {
      s.changeColor();
      return alphaBeta(s, depth - 1, alpha, beta, !maximizing);
    }

    if (maximizing) {
      int maxEval = INT_MIN;
      for (auto [x, y] : moves) {
        State next = s;
        next.makeMove(next.color, x, y);
        next.changeColor();
        int eval = alphaBeta(next, depth - 1, alpha, beta, false);
        maxEval = max(maxEval, eval);
        alpha = max(alpha, eval);
        if (beta <= alpha) break;
      }
      return maxEval;
    } else {
      int minEval = INT_MAX;
      for (auto [x, y] : moves) {
        State next = s;
        next.makeMove(next.color, x, y);
        next.changeColor();
        int eval = alphaBeta(next, depth - 1, alpha, beta, true);
        minEval = min(minEval, eval);
        beta = min(beta, eval);
        if (beta <= alpha) break;
      }
      return minEval;
    }
  }

  pair<int, int> findBestMove(State& s, int depth) {
    vector<pair<int, int>> moves = s.generateMoves(s.color);
    printMoves(moves);
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (auto [x, y] : moves) {
      State next = s;
      next.makeMove(next.color, x, y);
      next.changeColor();
      int score = alphaBeta(next, depth - 1, INT_MIN, INT_MAX, false);
      if (score > bestScore) {
        bestScore = score;
        bestMove = {x, y};
      }
    }
    return bestMove;
  }
};

int main() {
  State s;
  s.myColor = s.color = WHITE;
  Agent a;
  double t0, t1;
  cout << "RDY\n";
  fflush(stdout);
  while(true) {
    string inp; cin >> inp;
    if(inp == "BYE") break;
    else if(inp == "UGO") {
      cin >> t0 >> t1;
      s.myColor = s.color = BLACK;
      auto [x, y] = a.findBestMove(s, 4);
      cout << "IDO " << x << " " << y << "\n";
      fflush(stdout);
      s.makeMove(s.myColor, x, y);
      s.changeColor();
    } else if(inp == "HEDID") {
      int x, y;
      cin >> t0 >> t1 >> x >> y;
      s.makeMove(-s.myColor, x, y);
      s.changeColor();
      auto m = a.findBestMove(s, 4);
      x = m.first, y = m.second;
      cout << "IDO " << x << " " << y << "\n";
      fflush(stdout);
      s.makeMove(s.myColor, x, y);
    } else if(inp == "ONEMORE") {
      cout << "RDY\n";
      fflush(stdout);
      s = State();
      s.myColor = WHITE;
    }
  }
  return 0;
}