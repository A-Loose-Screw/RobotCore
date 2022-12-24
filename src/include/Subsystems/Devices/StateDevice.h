#ifndef RBC_STATE_DEVICE_H
#define RBC_STATE_DEVICE_H

#include <string>
#include "Loops/LoopSystem.h"

namespace RBC {
namespace Subsystems {
namespace Devices {

  /**
   * @brief State Device base.
   * 
   * A device with it's own loop
   * 
   */
  class StateDeviceBase : public Loops::LoopSystem {
   public:
    StateDeviceBase(std::string name = "<no name state device>") : Loops::LoopSystem(name) {}

    virtual std::string getStateString() = 0; // override me
    std::string getName() { return getSystemName(); }
  };

  /**
   * @brief State device.
   * A device which has it's own loop and can only act in one state at any given moment
   * 
   * @tparam StateType 
   */
  template <typename StateType>
  class StateDevice : public StateDeviceBase {
   public:
    StateDevice(std::string name = "<State Device>", StateType initialState = (StateType)0) : StateDeviceBase(name), _state(initialState) {}

    virtual void onLoopUpdate(double dt) final {
      if (_state != _lastState) {
        onStateChange(_state, _lastState);
        _lastState = _state;
      }

      onStateUpdate(_state, dt);
    }
   protected:
    void setState(StateType state) { _state = state; }

    virtual void onStateChange(StateType newState, StateType oldState) {}
    virtual void onStateUpdate(StateType state, double dt) = 0; // override me

    StateType _state, _lastState;
  };
  // class StateDeviceBase 
} // Devices
} // Subsystem
} // RBC

#endif