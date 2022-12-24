#include "Timing/Timing.h"
#include "PlatformUtils/Platform.h"
#include <algorithm>
#include <thread>
#include <iomanip>

#ifdef RBC_PLATFORM_UNIX
#include <time.h>
#include <unistd.h>
#endif


using namespace RBC::Timing;

using d_ms = std::chrono::duration<double, std::milli>;
using d_micro = std::chrono::duration<double, std::micro>;

double RBCTimer::getTimestamp_micro() {
  stop = clock::now();
  return std::chrono::duration_cast<d_micro>(stop-start).count();
}

double RBCTimer::getTimestamp_ms() {
  stop = clock::now();
  return std::chrono::duration_cast<d_ms>(stop-start).count();
}

double RBCTimer::getTimestamp_s() {
  return getTimestamp_ms()/1000.0;
}

void RBCTimer::sleepUntil(time_stamp time) {
  #ifdef RBC_PLATFORM_LINUX
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = getDuration_nano(clock::now(), time);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
  #elif defined(RBC_PLATFORM_MACOS)
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = getDuration_nano(clock::now(), time);
    nanosleep(&ts, NULL);
  #elif defined(RBC_PLATFORM_WINDOWS)

    Sleep()
  #else
    while (clock::now() < time) continue;
  #endif
}

void RBCTimer::sleepFor(duration time) {
  // auto t = clock::now();
  // while ((clock::now() - t).count() < time.count()) continue;
}

void RBCTimer::sleepFor(double time) {
  // auto t = clock::now();
  // while ((clock::now() - t).count() < time) continue;
}

long long RBCTimer::getDuration_nano(time_stamp first, time_stamp second) {
  return (std::chrono::duration_cast<std::chrono::duration<long long, std::nano>>(second-first).count());
}

long double RBCTimer::getDuration_micro(time_stamp first, time_stamp second) {
  return (std::chrono::duration_cast<std::chrono::duration<long double, std::micro>>(second-first).count());
}

long double RBCTimer::getDuration_ms(time_stamp first, time_stamp second) {
  return (std::chrono::duration_cast<std::chrono::duration<long double, std::milli>>(second-first).count());
}

long double RBCTimer::getDuration_s(time_stamp first, time_stamp second) {
  return getDuration_ms(first, second)/1000.0;
}