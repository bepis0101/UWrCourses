// Borys Adamiak 337295
#include "timer.h"

void Timer::reset() {
  start_time = std::chrono::high_resolution_clock::now();
}

int64_t Timer::elapsed() {
  return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now()-start_time).count();
}

int64_t Timer::now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
int64_t Timer::now_precise() {
  return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
