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

      virtual void onUpdate(double dt) = 0;
      virtual void onStart() {};
      virtual void onStop() {};

     private:
      std::string _name;
    };
  } // Subsystem
} // RBC

#endif