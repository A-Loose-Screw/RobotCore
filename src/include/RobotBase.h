#ifndef RBC_ROBOT_BASE_H
#define RBC_ROBOT_BASE_H

#include <string>

namespace RBC {

  /**
   * @brief Main Derived class for creating a RobotCoreLib Robot
   * 
   */
  class RobotBase {
   public:
    RobotBase(const std::string &name = "RBC-Program");
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
    void shutdown();

   private:
    static RobotBase *_instance;
    bool _running = false;
    bool _enabled = false;

    std::string _name;
  };

  RobotBase *createRobot();
}

#define RBC_ROBOT_MAIN(ROBOT) RBC::RobotBase *RBC::createRobot() { return new ROBOT(); }

#endif