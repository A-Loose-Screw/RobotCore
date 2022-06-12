#include "RobotBase.h"

#include <iostream>

extern RBC::RobotBase *RBC::createRobot();

int main(int argc, char** argv) {

  auto robot = RBC::createRobot();
  int returner = robot->run();
  return returner;
}