#ifndef RBC_ROBOT_BASE_H
#define RBC_ROBOT_BASE_H

#include <string>

#include "Timing/Timing.h"
#include "Subsystems/SubsystemController.h"

namespace RBC {

  /**
   * @brief Main Derived class for creating a RobotCoreLib Robot
   * 
   */
  class RobotBase : public Subsystems::SubsystemController {
   public:
    RobotBase(const std::string &name = "RBC-Program", int argc = 0, char** argv = (char**)"");
    virtual ~RobotBase();

    /**
     * @brief Get the singleton of the class (instance)
     * 
     * @return RobotBase& 
     */
    static RobotBase &get() {
      return *_instance;
    }

    /**
     * @brief Main entry for robot base & super loop starter
     * 
     * @return int 
     */
    int run();

    /**
     * @brief Runs when robot is first initialised/booted
     * 
     */
    virtual void robotInit() {}

    /**
     * @brief Runs periodically after robot init (looping code)
     * 
     */
    virtual void robotPeriodic() {}

    /**
     * @brief Runs once, when robot is set to enabled
     * 
     */
    virtual void enabledInit() {}

    /**
     * @brief Runs periodically after robot has been enabled. (looping code)
     * 
     */
    virtual void enabledPeriodic() {}

    /**
     * @brief Set the robot to enabled
     * 
     * @param enable 
     */
    void setEnabled(bool enable = true);

    /**
     * @brief Returns if the robot is enabled or not
     * 
     * @return true 
     * @return false 
     */
    bool isEnabled() {
      return _enabled;
    }

    /**
     * @brief Get the Up Time in seconds
     * 
     * @return double 
     */
    double getUpTime() {
      return RBC::Timing::RBCTimer::getTimestamp_s();
    }

    double getDt() {
      return _dt;
    }

    /**
     * @brief Get the Name of the robot
     * 
     * @return std::string 
     */
    std::string getName() {
      return _name;
    }

    /**
     * @brief Shutdown the robot
     * 
     */
    void shutdown(int returner = 0);

    /**
     * @brief Get the Args object
     * 
     * @return std::pair<int, char**> 
     */
    std::pair<int, char**> getArgs() {
      return {_argc, _argv};
    }

   private:
    static RobotBase *_instance;
    bool _running = false;
    bool _enabled = false;

    double _dt = 0;

    int _returner = 0;
    int _argc;
    char** _argv;

    std::string _name;
  };

  RobotBase *createRobot(int argc, char** argv);
}

#define RBC_ROBOT_MAIN(ROBOT) RBC::RobotBase *RBC::createRobot(int argc, char** argv) { return new ROBOT(argc, argv); }

#endif