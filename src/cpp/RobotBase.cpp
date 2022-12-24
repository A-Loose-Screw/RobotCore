#include "RobotBase.h"
#include "Logging/Print.h"
#include "ErrorHandles/Assert.h"

#include <iostream>

using namespace RBC;
using namespace std::chrono;

RobotBase *RobotBase::_instance = nullptr;

RobotBase::RobotBase(const std::string &name, int argc, char** argv) : SubsystemController("<" + name + " - Loop Controller>") {
  RBC_CORE_ASSERT(!_instance, "A Robot instance already exists. Cannot create another");
  RBC_CORE_PRINT_WARN("Robot Constructed");

  _instance = this;
  _name = name;
  _argc = argc;
  _argv = argv;
}

RobotBase::~RobotBase() {
  RBC_CORE_PRINT_WARN("Robot Deconstructed");
}

void RobotBase::setEnabled(bool enable) {
  // Enable if not already enabled
  if (!_enabled && enable) {
    _enabled = true;
    enabledInit();
    RBC_CORE_PRINT_WARN("Robot Enabled");

    // If already enabled, and enable is false. Disable
  } else if (_enabled && !enable) {
    _enabled = false;
    RBC_CORE_PRINT_WARN("Robot Disabled");
  }
}

int RobotBase::run() {
  RBC_CORE_ASSERT(!_running, "Super loop already exists, cannot start another");
  RBC_CORE_PRINT_WARN("Robot Starting");
  _running = true;
  
  // Timing
  auto now = Timing::RBCTimer::getSystemTimestamp();
  auto prev = now;
  _dt = (duration_cast<duration<double, std::milli>>(now-prev).count())/1000.0;

  robotInit();
  init();
  RBC_CORE_PRINT_WARN("Robot Initialised");

  // Main super loop
  while (_running) {
    prev = now;
    now = Timing::RBCTimer::getSystemTimestamp();
    _dt = (duration_cast<duration<double, std::milli>>(now-prev).count())/1000.0;

    /**
     * -------- Start Main Code
     */
    robotPeriodic();
    updateLoopController();
    if (_enabled) {
      enabledPeriodic();
    }

    /**
     * -------- End Main Code
     */
  }

  stopLoops();

  return _returner;
}

void RobotBase::shutdown(int returner) {
  RBC_CORE_PRINT_ERROR("Shutdown Called!");
  _returner = returner;
  _running = false;
}