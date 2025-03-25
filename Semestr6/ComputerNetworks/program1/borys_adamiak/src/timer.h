// Borys Adamiak 337295
#include <chrono>

class Timer {
  public:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
  Timer() : start_time(std::chrono::high_resolution_clock::now()) {}
  void reset();

  int64_t elapsed();
  int64_t now();
  int64_t now_precise();

};