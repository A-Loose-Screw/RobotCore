#include "RobotBase.h"

using namespace RBC;

RobotBase *RobotBase::_instance = nullptr;

RobotBase::RobotBase(const std::string &name) {
  _instance = this;
  _name = name;
}

RobotBase::~RobotBase() {}

void RobotBase::setEnabled(bool enable) {
  // If the robot is not enabled, enable the robot
  if (!_enabled && enable) {
    _enabled = true;
    enabledInit();

  // If the robot is enabled (and we want to disable). Disable the robot
  } else if (_enabled && !enable) {
    _enabled = false;
  }
}


int RobotBase::run() {
  _running = true;

  robotInit();
  
  while (_running) {
    robotPeriodic();
    if (_enabled) {
      enabledPeriodic();
    }
  }

  return 0;
}

void RobotBase::shutdown() {
  _running = false;
}