#include <algorithm>
#include <thread>
#include <iomanip>
#include "Subsystems/Loops/LoopSystem.h"
#include "Logging/Print.h"
#include "PlatformUtils/Platform.h"

#ifdef RBS_PLATFORM_WINDOWS
#include <windows.h>
LARGE_INTEGER frequency, start, current;

QueryPerformanceFrequency(&frequency);
QueryPerformanceCounter(&start);
#endif

using namespace RBC::Subsystems::Loops;
using namespace RBC::Timing;
using namespace std::chrono;



void LoopSystem::setLoop(unsigned int hz) {
  if (hz > 0 && hz < 1000000) {
    _freq = hz;
  }
}

void LoopSystem::updateLoop() {
  if (!_start) return;
  if (!_running) {
    _next = RBCTimer::getSystemTimestamp();
    _prev = _next - (1000ms/std::max(1u, _freq));
    _now = RBCTimer::getSystemTimestamp();
    _running = true;
  }
  _prev = _now;
  _now = RBCTimer::getSystemTimestamp();

  double dt = RBCTimer::getDuration_s(_prev, _now);
  _dt = dt;
  onLoopUpdate(dt);

  if (_freq > 0) {
    _next += (1000ms/_freq);
    RBCTimer::sleepUntil(_next);
  }
}

void LoopSystem::manual_update() {
  if (!_start) return;
  if (!_running) {
    _now = RBCTimer::getSystemTimestamp();
    _prev = _now;
    _running = true;
  }
  _prev = _now;
  _now = RBCTimer::getSystemTimestamp();

  double dt = RBCTimer::getDuration_s(_prev, _now);
  _dt = dt;

  onLoopUpdate(dt);
}

void LoopSystem::startLoop(unsigned int hz) {
  if (hz > 0) setLoop(hz);
  _start = true;
  onLoopStart();
}

void LoopSystem::stopLoop() {
  _start = false;
  _running = false;
  onLoopStop();
}

bool LoopSystem::isLoopRunning() {
  return _running;
}