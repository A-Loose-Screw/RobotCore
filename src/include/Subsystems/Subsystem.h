#ifndef RBC_SUBSYSTEM_H
#define RBC_SUBSYSTEM_H

#include <string>
#include "Loops/LoopSystem.h"

namespace RBC {
namespace Subsystems {
  class Subsystem : public Loops::LoopSystem {
    public:
    Subsystem(std::string name) : Loops::LoopSystem(name) {
      _name = name;
    }

    // virtual void onLoopUpdate(double dt) = 0; // override me
    // virtual void onLoopStart() {};
    // virtual void onLoopStop() {};

    private:
    std::string _name;
  };
} // Subsystem
} // RBC

#endif