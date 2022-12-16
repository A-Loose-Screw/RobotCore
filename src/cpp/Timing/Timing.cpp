#include "Timing/Timing.h"

using namespace RBC::Timing;
using namespace std::chrono;

using d_ms = duration<double, std::milli>;
using d_micro = duration<double, std::micro>;

double RBCTimer::getTimestamp_micro() {
  stop = high_resolution_clock::now();
  return duration_cast<d_micro>(stop-start).count();
}

double RBCTimer::getTimestamp_ms() {
  stop = high_resolution_clock::now();
  return duration_cast<d_ms>(stop-start).count();
}

double RBCTimer::getTimestamp_s() {
  return getTimestamp_ms()/1000.0;
}