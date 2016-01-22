#include "Timer.h"

std::chrono::time_point<std::chrono::system_clock> Timer::startTime = std::chrono::high_resolution_clock::now();
double Timer::actualTime = 0;
bool Timer::timerOn = false;

void Timer::setActualTime() { actualTime = std::chrono::duration_cast<std::chrono::milliseconds>(
              std::chrono::high_resolution_clock::now() - startTime)
              .count() / 1000.;}
