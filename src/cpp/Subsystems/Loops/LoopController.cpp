#include <thread>
#include <iostream>
#include <sstream>
#include "Logging/Print.h"
#include "Subsystems/Loops/LoopController.h"

using namespace RBC::Subsystems::Loops;
using namespace RBC::Timing;
using namespace std::chrono;


void LoopController::registerLoop(LoopSystem *loopSystem) {
  _loopScheduleList.push_back({loopSystem});
}

void LoopController::registerAsyncLoop(LoopSystem *loopSystem) {
  _asyncLoopList.push_back({loopSystem, this});
}

void LoopController::init() {
  unsigned int highest_frequency = 0;
  for (auto &loop : _loopScheduleList) {
    highest_frequency = loop.system->_freq > highest_frequency ? loop.system->_freq : highest_frequency;
  }

  _control_loop_frequency = highest_frequency;

  _next = RBCTimer::getSystemTimestamp();
  _prev = _next - (1000ms/std::max(1u, _control_loop_frequency));
  _now = RBCTimer::getSystemTimestamp();

  for (auto &asyncLoop : _asyncLoopList) {
    asyncLoop.start();
  }
}

void LoopController::stopLoops() {
  for (auto &loop : _loopScheduleList) {
    loop.system->stopLoop();
  }

  for (auto &asyncLoop : _asyncLoopList) {
    auto thread_id = asyncLoop.loop_t.get_id();
    std::stringstream ss;
    ss << thread_id;
    
    RBC_CORE_PRINT_WARN(getControllerName() + " Stopping Thread " + asyncLoop.system->getSystemName() + " ID: " + ss.str());
    asyncLoop.system->stopLoop();
    asyncLoop.stop();
    RBC_CORE_PRINT_INFO(getControllerName() + " Successfully Stopped Thread " + asyncLoop.system->getSystemName() + " ID: " + ss.str());
  }
}

void LoopController::update() {
  _prev = _now;
  _now = RBCTimer::getSystemTimestamp();

  // Loop Code Start
  for (auto &loop : _loopScheduleList) {
    if (_now >= loop.next_scheduled_epoch) {
      loop.system->manual_update();
      loop.next_scheduled_epoch += loop.system->_freq > 0 ? 1000ms/loop.system->_freq : 0ms;
    }
  }
  // Loop Code End

  if (_control_loop_frequency > 0) {
    _next += (1000ms/_control_loop_frequency);
    std::this_thread::sleep_until(_next);
  }
}

void LoopController::AsyncLoop::loop() {
  while (async_running) {
    system->update();
  }
}

void LoopController::AsyncLoop::start() {
  async_running = true;
  loop_t = std::thread(&LoopController::AsyncLoop::loop, this);

  auto thread_id = loop_t.get_id();
  std::stringstream ss;
  ss << thread_id;
  
  RBC_CORE_PRINT_INFO(controller->getControllerName() + " Started " + system->getSystemName() + " Thread, ID: " + ss.str());
}

void LoopController::AsyncLoop::stop() {
  async_running = false;
  loop_t.join();
}