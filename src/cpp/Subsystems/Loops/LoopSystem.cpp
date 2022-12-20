#include <algorithm>
#include <thread>
#include <iomanip>
#include "Subsystems/Loops/LoopSystem.h"
#include "Logging/Print.h"

using namespace RBC::Subsystems::Loops;
using namespace RBC::Timing;
using namespace std::chrono;

void LoopSystem::setLoop(unsigned int hz) {
  if (hz > 0 && hz < 1000000) {
    _freq = hz;
  }
}

void LoopSystem::update() {
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
  onUpdate(dt);

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
  onUpdate(dt);
}

void LoopSystem::startLoop(unsigned int hz) {
  if (hz > 0) setLoop(hz);
  _start = true;
  onStart();
}

void LoopSystem::stopLoop() {
  _start = false;
  _running = false;
  onStop();
}

bool LoopSystem::isLoopRunning() {
  return _running;
}