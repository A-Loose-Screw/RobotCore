#include "Timing/FrequencyController.h"
#include "Logging/Print.h"

using namespace RBC::Timing;
using namespace std::chrono;

void FrequencyController::init(unsigned int hz) {
  _freq = hz;
  _next = RBCTimer::getSystemTimestamp();
}

void FrequencyController::sleep_to_next_epoch() {
  #ifdef RBC_PLATFORM_WINDOWS
    if (_freq > 0) {
      _next += (1000ms/_freq);
      // std::cout << "Duration: " << RBCTimer::getDuration_ms(RBCTimer::getSystemTimestamp(), _next) << std::endl;
      while (RBCTimer::getDuration_ms(RBCTimer::getSystemTimestamp(), _next) > 0) continue;
    }
  #elif defined(RBC_PLATFORM_LINUX) || defined(RBC_PLATFORM_MACOS)
    if (_freq > 0) {
      _next += (1000ms/_freq);
      if (RBCTimer::getSystemTimestamp() < _next) {
        RBCTimer::sleepUntil(_next);
      }
    }
  #else
    RBC_CORE_PRINT_ERROR("Cannot control frequency for unknown platform");
  #endif
}