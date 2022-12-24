#include <algorithm>
#include <thread>
#include <iomanip>
#include "Subsystems/Loops/LoopSystem.h"
#include "Logging/Print.h"
#include "PlatformUtils/Platform.h"

using namespace RBC::Subsystems::Loops;
using namespace RBC::Timing;
using namespace std::chrono;

void LoopSystem::setLoop(unsigned int hz) {
  if (hz > 0 && hz < 1000000) {
    _freq = hz;
    _freq_controller.init(_freq);
  }
}

void LoopSystem::updateLoop() {
  if (!_start) return;
  if (!_running) {
    _now = RBCTimer::getSystemTimestamp();
    _prev = _now - (1000ms/std::max(1u, _freq));
    _running = true;
  }
  _prev = _now;
  _now = RBCTimer::getSystemTimestamp();

  double dt = RBCTimer::getDuration_s(_prev, _now);
  _dt = dt;
  onLoopUpdate(dt);

  _freq_controller.sleep_to_next_epoch(); // make thread sleep
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