#ifndef RBC_STRATEGY_H
#define RBC_STRATEGY_H

#include <string>

namespace RBC {
namespace Subsystems {
namespace Strategy {
  enum class StrategyState {
    //! Initialized, but never run. The default state.
    INITIALIZED = 0,
    //! Currently running or active
    RUNNING,
    //! Strategy was rejected from starting as the current strategy may not be interrupted
    CANCELLED,
    //! Strategy was voluntarily marked as complete, using SetDone
    DONE,
    //! Strategy has timed out
    TIMED_OUT,
    //! Strategy was interrupted by another strategy
    INTERRUPTED
  };


  /**
   * @brief Strategy Class
   * 
   * A 'Strategy' is one component in a sequential chain of events or actions.
   * Designed to be one of many strategies in a chain to represent step by step state changes and control
   * 
   * Strategies run on a slow loop while the 'StrategySystem' run on a faster loop set on startup.
   * Standardized strategy designs recommend building a strategy to orchestrate a system, 
   * while the system itself should provide control logic in a faster loop.
   */
  class Strategy {
   public:
    Strategy(std::string name = "<no name>") : _strategy_name(name) {}

    virtual std::string getName() {
      return _strategy_name;
    }

    virtual void onUpdate(double dt) = 0; // override me
    virtual void onStart() {}
    virtual void onStop() {}

    void setCanBeInterrupted(bool interruptable) {
      _can_interrupt = interruptable;
    }

    void setCanBeReused(bool reusable) {
      _can_reuse = reusable;
    }

    void setPassive(bool passive) {
      _is_passive = passive;
    }

    bool interrupt() {
      if (_can_interrupt) {
        return true;
      }

      return false;
    }

   protected:

    void start() {
      if (_strategy_state != StrategyState::RUNNING) {
        _time = 0;
        _strategy_state = StrategyState::RUNNING;
        onStart();
      }
    }

    void update(double dt) {
      if (_strategy_state == StrategyState::INITIALIZED) {
        start();
      }

      if (_strategy_state == StrategyState::RUNNING) {
        onUpdate(dt);
        _time += dt;

        if (_timeout > 0 && _time > _timeout) {
          stop(StrategyState::TIMED_OUT);
        }
      }
    }

    void stop(StrategyState newState) {
      StrategyState oldState = _strategy_state;
      _strategy_state = newState;

      if (oldState == StrategyState::RUNNING) {
        onStop();
      }
    }

   private:
    std::string _strategy_name;
    double _time = 0;
    double _timeout = 0;
    bool _can_reuse = false;
    bool _can_interrupt = false;
    bool _is_passive = false;

    StrategyState _strategy_state = StrategyState::INITIALIZED;
  };
} // Strategy
} // Subsystems
} // RBC

#endif