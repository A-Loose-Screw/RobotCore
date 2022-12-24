#ifndef RBC_FREQ_CONTROLLER_H
#define RBC_FREQ_CONTROLLER_H

#include "PlatformUtils/Platform.h"
#include "Timing.h"

namespace RBC {
namespace Timing {

  class FrequencyController {
   public:

    /**
     * @brief Initialize the controller with the frequency in hz
     * 
     * @param hz 
     */
    void init(unsigned int hz);

    /**
     * @brief halt thread until next epoch
     * 
     */
    void sleep_to_next_epoch();
   private:
    unsigned int _freq = 0;
    RBCTimer::time_stamp _next;
  };

} // Timing
} // RBC

#endif