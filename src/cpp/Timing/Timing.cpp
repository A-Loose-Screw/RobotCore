#include "Timing/Timing.h"
#include <algorithm>
#include <thread>
#include <iomanip>

using namespace RBC::Timing;
using namespace std::chrono;

using d_ms = duration<double, std::milli>;
using d_micro = duration<double, std::micro>;

double RBCTimer::getTimestamp_micro() {
  stop = clock::now();
  return duration_cast<d_micro>(stop-start).count();
}

double RBCTimer::getTimestamp_ms() {
  stop = clock::now();
  return duration_cast<d_ms>(stop-start).count();
}

double RBCTimer::getTimestamp_s() {
  return getTimestamp_ms()/1000.0;
}

void RBCTimer::sleepUntil(time_stamp time) {
  while (clock::now() < time) continue;
}

void RBCTimer::sleepFor(duration time) {
  auto t = clock::now();
  while ((clock::now() - t).count() < time.count()) continue;
}

void RBCTimer::sleepFor(double time) {
  auto t = clock::now();
  while ((clock::now() - t).count() < time) continue;
}

double RBCTimer::getDuration_micro(time_stamp first, time_stamp second) {
  return (duration_cast<std::chrono::duration<double, std::micro>>(second-first).count());
}

double RBCTimer::getDuration_ms(time_stamp first, time_stamp second) {
  return (duration_cast<std::chrono::duration<double, std::milli>>(second-first).count());
}

double RBCTimer::getDuration_s(time_stamp first, time_stamp second) {
  return getDuration_ms(first, second)/1000.0;
}