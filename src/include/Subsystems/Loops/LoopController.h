#ifndef RBC_LOOP_CONTROLLER_H
#define RBC_LOOP_CONTROLLER_H

#include <atomic>
#include <thread>
#include <vector>
#include <string>
#include "LoopSystem.h"


namespace RBC {
namespace Subsystems {
namespace Loops {
  class LoopController {
    public:
    LoopController(const std::string &name = "<Loop Controller>") {
      _controllerName = name;
    } 
    /**
     * @brief Register a loop system to the queue
     * 
     * @param loopSystem
     */
    void registerLoop(LoopSystem *loopSystem);

    /**
     * @brief Register an asynchronous loop that runs on separate thread from main
     * 
     * @param loopSystem 
     */
    void registerAsyncLoop(LoopSystem *loopSystem);

    /**
     * @brief Update every registered loop
     * 
     */
    void updateLoopController();

    /**
     * @brief Initialise each loop
     * 
     */
    void init();

    /**
     * @brief Stop each loop
     * For async loops this will join them sequentially in order
     */
    void stopLoops();

    /**
     * @brief Get the Dt
     * 
     * @return double 
     */
    double getDt() { return _dt; }

    /**
     * @brief Get the Current Frequency in hz
     * 
     * @return double 
     */
    double getCurrentFrequency() { return 1.0/getDt(); };

    /**
     * @brief Get the Controller Name
     * 
     * @return std::string 
     */
    std::string getControllerName() {
      return _controllerName;
    }
  
    private:
    Timing::RBCTimer::time_stamp _now;
    Timing::RBCTimer::time_stamp _next;
    Timing::RBCTimer::time_stamp _prev;

    double _dt = 0;

    protected:
    struct LoopSchedule {
      LoopSystem *system;
      Timing::RBCTimer::time_stamp next_scheduled_epoch = Timing::RBCTimer::getSystemTimestamp(); // when next the loop is scheduled to run
    };

    struct AsyncLoop {
      LoopSystem *system;
      LoopController *controller;
      bool async_running = false;
      std::thread loop_t;
      void loop();
      void start();
      void stop();
    };
    
    unsigned int _control_loop_frequency = 0; // the control loop frequency.
    bool _use_custom_freq = false;
    std::vector<LoopSchedule> _loopScheduleList; // stores the Query for a loop.
    std::vector<AsyncLoop> _asyncLoopList; // stores all the registered async loops

    std::string _controllerName;
  };
} // Loops
} // Subsystems
} // RBC

#endif