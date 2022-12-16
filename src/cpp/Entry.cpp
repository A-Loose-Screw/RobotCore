#include "Logging/Print.h"
#include "RobotBase.h"

#include <iostream>

extern RBC::RobotBase *RBC::createRobot(int argc, char** argv);

/**
 * @brief Main entrypoint into the program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {
  /**
   * @brief Initialize pre startup & logger
   * 
   */
  RBC::Log::init("[Robot Pre-Startup]");

  
  /**
   * @brief Create Robot Class (supports only 1)
   * 
   */
  auto robot = RBC::createRobot(argc, argv);

  /**
   * @brief Setup Logger for Core & Client
   * 
   */
  RBC_CORE_PRINT_INFO("Robot Program - " + robot->getName() + " Started");
  RBC::Log::setClientName("[Runtime - " + robot->getName() + "]");

  /**
   * @brief Runtime/Super Loop
   * 
   */
  int returner = robot->run();

  /**
   * @brief Setup logger for killtime
   * 
   */
  RBC::Log::setClientName("[Killtime - " + robot->getName() + "]");

  /**
   * @brief App cleanup
   * 
   */
  delete robot;
  RBC_CORE_PRINT_INFO("Robot Program Ended");
  return returner;
}