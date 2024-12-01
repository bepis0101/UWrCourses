#include <bits/stdc++.h>

using namespace std;

const int MAX_DIST = 150;
const int MAX_ROUNDS = 200;
const int MAX_PRESENTS_FALLEN = 30;

const int WIDTH = 1920;
const int HEIGHT = 750;

char grid[HEIGHT][WIDTH];

int distance(int x1, int y1, int x2, int y2) {
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
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


class Gargoyle {
public:
  int x;
  int y;
  int cooldown;
  Gargoyle() {
    this->x = 0;
    this->y = 0;
    this->cooldown = 1;
  }
  Gargoyle(int x, int y, int cooldown = 1) {
    this->x = x;
    this->y = y;
    this->cooldown = cooldown;
  }

  void move(int x, int y) {
    this->x = x;
    this->y = y; 
  }
};

class Present {
public:  
  int id;
  int value;
  int x;
  int y;
  int vy;
  bool is_destroyed;
  
  Present() {
    this->id = -1;
    this->value = 0;
    this->x = 0;
    this->y = 0;
    this->vy = 1;
    this->is_destroyed = true;
  }
  Present(int id, int value, int x, int y, int vy) {
    this->id = id;
    this->value = value;
    this->x = x;
    this->y = y;
    this->vy = vy;
    this->is_destroyed = false;
  }
};

class State {
public:
  int score;
  int num_of_gargoyles;
  vector<Gargoyle> gargoyles;
  int num_of_presents;
  vector<Present> presents;
  default_random_engine generator;
  int calc_score;
  State() {
    this->score = 0;
    this->num_of_gargoyles = 1;
    this->gargoyles = {};
    this->num_of_presents = 0;
    this->presents = {};
  }
  State(int score, int num_of_gargoyles, vector<Gargoyle> gargoyles, int num_of_presents, vector<Present> presents) {
    this->score = score;
    this->num_of_gargoyles = num_of_gargoyles;
    this->gargoyles = gargoyles;
    this->num_of_presents = num_of_presents;
    this->presents = presents;
    this->calc_score = 0;
  }
  int evaluate() {
    int curr_score = score;
    // jeżeli gargulec jest obok prezentu zostaje on zniszczony
    for(int g = 0; g < num_of_gargoyles; g++) {
      for(int p = 0; p < num_of_presents; p++) {
        if(presents[p].y < presents[p].vy) {
          presents[p].is_destroyed = true;
          continue;
        }
        if(presents[p].is_destroyed) {
          continue;
        }
        if(distance(gargoyles[g].x, gargoyles[g].y, presents[p].x, presents[p].y-presents[p].vy) <= 30) {
          curr_score += 5*presents[p].value;
          presents[p].is_destroyed = true;
        }
      }
    }
    calc_score = curr_score;
    return curr_score;
  }

  void draw_random() {
    for(int g = 0; g < num_of_gargoyles; g++) {
      uniform_int_distribution<int> distribution_x(max(0, gargoyles[g].x-MAX_DIST), min(WIDTH, gargoyles[g].x+MAX_DIST));
      uniform_int_distribution<int> distribution_y(max(0, gargoyles[g].y-MAX_DIST), min(HEIGHT, gargoyles[g].y+MAX_DIST));
      int draw_x = distribution_x(generator);
      int draw_y = distribution_y(generator);
      while(distance(draw_x, draw_y, gargoyles[g].x, gargoyles[g].y) > MAX_DIST) {
        draw_x = distribution_x(generator);
        draw_y = distribution_y(generator);
      }
      gargoyles[g].move(draw_x, draw_y);
    }
  }

  void draw_closest() {
    for(int g = 0; g < num_of_gargoyles; g++) {
      Present closest;
      int min_dist = INT_MAX;
      for(int p = 0; p < num_of_presents; p++) {
        if(presents[p].is_destroyed) continue;
        if(presents[p].y-presents[p].vy < 0) continue;
        int dist = distance(gargoyles[g].x, gargoyles[g].y, presents[p].x, presents[p].y-presents[p].vy);
        if(dist < min_dist) {
          closest = presents[p];
          min_dist = dist;
        }
      }
      if(closest.id == -1) continue;
      if(min_dist < 150) {
        gargoyles[g].move(closest.x, closest.y-closest.vy);
      } else {
        double angle = atan2(closest.y-closest.vy-gargoyles[g].y, closest.x - gargoyles[g].x);
        gargoyles[g].move(gargoyles[g].x + MAX_DIST*cos(angle), gargoyles[g].y + MAX_DIST*sin(angle));
      }
    }
  }
};



/**
 * Kieruj swoimi gargulacami aby złapać więcej prezentów i zdobyć więcej punktów niż drużyna przeciwnika.
 **/

int main()
{
  int gargoyles_per_player; // liczba gargulców w drużynie
  cin >> gargoyles_per_player; cin.ignore();
  vector<Gargoyle> gargoyles(gargoyles_per_player);
  // game loop
  while (1) {
    int missed_presents_to_end; // ile prezentów musi jeszcze spaść na ziemię aby gra się zakończyła
    cin >> missed_presents_to_end; cin.ignore();
    int my_score; // mój wynik
    cin >> my_score; cin.ignore();
    for (int i = 0; i < gargoyles_per_player; i++) {
      int x; // pozycja na współrzędnej x
      int y; // pozycja na współrzędnej y
      int cooldown; // liczba tur aż będzie dostępna kula ognia, 0 oznacza możliwość rzucenia czaru
      cin >> x >> y >> cooldown; cin.ignore();
      gargoyles[i] = Gargoyle(x, y, cooldown);
    }
    int foe_score; // wynik oponenta
    cin >> foe_score; cin.ignore();
    for (int i = 0; i < gargoyles_per_player; i++) {
      int x;
      int y;
      int cooldown;
      cin >> x >> y >> cooldown; cin.ignore();
    }
    int entity_count; // liczba spadających obiektów
    cin >> entity_count; cin.ignore();
    vector<Present> presents(entity_count);
    for (int i = 0; i < entity_count; i++) {
      int id; // unikalny identyfikator spadającego obiektu
      int value; // wartość prezentu
      int x;
      int y;
      int vy; // szybkość spadania obiektu w pionie
      cin >> id >> value >> x >> y >> vy; cin.ignore();
      presents[i] = Present(id, value, x, y, vy);
    }
    Timer t;
    State s(my_score, gargoyles_per_player, gargoyles, entity_count, presents);
    State maks = s;
    while(t.elapsed() < 50) {
      s.draw_closest();
      if(s.evaluate() > maks.calc_score) {
        maks = s;
      }
      s.draw_random();
      if(s.evaluate() > maks.calc_score) {
        maks = s;
      }
    }
    for(int i = 0; i < gargoyles_per_player; i++) {
      cout << "FLY " << maks.gargoyles[i].x << ' ' << maks.gargoyles[i].y << endl;
    }
  }
}