#include "Timer.h"

std::chrono::time_point<std::chrono::system_clock> Timer::current_time;
std::chrono::time_point<std::chrono::system_clock> Timer::last_time;

float Timer::delta_time = 0.0f;
float Timer::acc_time = 0.0f;