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

  double dt = (duration_cast<duration<double, std::milli>>(_now-_prev).count())/1000.0;
  onUpdate(dt);

  if (_freq > 0) {
    _next += (1000ms/_freq);
    std::this_thread::sleep_until(_next);
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

  double dt = (duration_cast<duration<double, std::milli>>(_now-_prev).count())/1000.0;
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