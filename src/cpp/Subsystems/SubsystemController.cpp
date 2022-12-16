#include "Subsystems/SubsystemController.h"

using namespace RBC::Subsystems;

void SubsystemController::setControlLoopFrequency(unsigned int hz) {
  _use_custom_freq = true;
  _control_loop_frequency = hz;
}