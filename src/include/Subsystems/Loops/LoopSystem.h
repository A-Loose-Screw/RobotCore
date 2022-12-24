#ifndef RBC_LOOP_SYSTEM_H
#define RBC_LOOP_SYSTEM_H

#include <string>
#include "Timing/Timing.h"

namespace RBC {
namespace Subsystems {
namespace Loops {
  class LoopSystem {
    public:
    LoopSystem(const std::string &name = "<Loop System>") {
      _systemName = name;
    }
    
    /**
     * @brief Run looping logic
     * 
     * @param dt 
     */
    virtual void onLoopUpdate(double dt) = 0; // override me

    /**
     * @brief Run logic on start
     * 
     */
    virtual void onLoopStart() {};

    /**
     * @brief Run logic on stop
     * 
     */
    virtual void onLoopStop() {};

    /**
     * @brief Called as the main loop system controller, calculates dt using timer and sets frequency
     * 
     */
    void updateLoop();

    /**
     * @brief Start loop with frequency, 50-100 are normal amounts, if not specified, will use the set frequency
     * 
     * @param hz 
     */
    void startLoop(unsigned int hz = 0);

    /**
     * @brief Stop loop from running
     * 
     */
    void stopLoop();

    /**
     * @brief Set the Loop to a certain frequency
     * 
     * @param hz 
     */
    void setLoop(unsigned int hz);

    /**
     * @brief Check to see if the loop is running
     * 
     * @return true 
     * @return false 
     */
    bool isLoopRunning();

    /**
     * @brief Get the Dt off the loop
     * 
     * @return double 
     */
    double getDt() {
      return _dt;
    }

    /**
     * @brief Get the set frequency
     * 
     * @return unsigned int 
     */
    unsigned int getFreq() {
      return _freq;
    }

    /**
     * @brief Get the Current Frequency of loop in hz
     * 
     * @return double 
     */
    double getCurrentFreq() {
      return 1.0/_dt;
    }

    /**
     * @brief Get the Name of loop system
     * 
     * @return std::string 
     */
    std::string getSystemName() {
      return _systemName;
    }

    private:
    unsigned int _freq = 0;
    double _dt = 0;
    bool _running = false;
    bool _start = false;
    Timing::RBCTimer::time_stamp _now;
    Timing::RBCTimer::time_stamp _next;
    Timing::RBCTimer::time_stamp _prev;

    void manual_update(); // will update without updating frequency on thread
    std::string _systemName;
    friend class LoopController;
  };
} // Loops
} // Subsystems
} // RBC

#endif