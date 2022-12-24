#ifndef RBC_SUBSYSTEM_CONTROLLER_H
#define RBC_SUBSYSTEM_CONTROLLER_H

#include <string>
#include "Loops/LoopController.h"

namespace RBC {
namespace Subsystems {
  class SubsystemController : public Loops::LoopController {
    public:
    SubsystemController(std::string name) : LoopController(name) {
      _name = name;
    }

    /**
     * @brief Set the Control Loop Frequency
     * override the auto set frequency and set the main thread frequency in hz
     * Note that the main thread MUST be faster or equal to the fastest sub loop
     * 
     * @param hz
     */
    void setControlLoopFrequency(unsigned int hz);

    /**
     * @brief Get the Subsystem Loop Array object
     * 
     * @return std::vector<LoopSchedule> 
     */
    std::vector<LoopSchedule> &getSubsystemLoopArray() {
      return _loopScheduleList;
    }

    /**
     * @brief Get the Async Subsystem Loop Array object
     * 
     * @return std::vector<AsyncLoop>& 
     */
    std::vector<AsyncLoop> &getAsyncSubsystemLoopArray() {
      return _asyncLoopList;
    }

    /**
     * @brief Get the Subsystem Loop object
     * 
     * @param pos position
     * @return Loops::LoopSystem* 
     */
    Loops::LoopSystem *getSubsystemLoop(unsigned int pos) {
      return _loopScheduleList.at(pos).system;
    }

    /**
     * @brief Get the Async System Loop object
     * 
     * @param pos position
     * @return Loops::LoopSystem* 
     */
    Loops::LoopSystem *getAsyncSystemLoop(unsigned int pos) {
      return _asyncLoopList.at(pos).system;
    }

    private:
    std::string _name;
  };
} // Subsystem
} // RBC

#endif