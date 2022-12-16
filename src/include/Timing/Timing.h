#ifndef RBC_TIMING_H
#define RBC_TIMING_H

#include <chrono>
#include "PlatformUtils/Platform.h"

namespace RBC {
  namespace Timing {
    class RBCTimer {
     public:
      /**
       * @brief Get the Timestamp in microseconds
       * 
       * @return double 
       */
      static double getTimestamp_micro();

      /**
       * @brief Get the Timestamp in milliseconds
       * 
       * @return double 
       */
      static double getTimestamp_ms();

      /**
       * @brief Get the Timestamp in seconds
       * 
       * @return double 
       */
      static double getTimestamp_s();

      /**
       * @brief high resolution time_stamp
       * 
       */
      #ifdef RBC_MSC
      typedef std::chrono::high_resolution_clock::time_point time_stamp;
      #elif defined(RBC_GCC) || defined(RBC_CLANG)
      typedef std::chrono::_V2::high_resolution_clock::time_point time_stamp;
      #else
      #error "Compiler not supported"
      #endif

      /**
       * @brief Get the System Timestamp
       * 
       * @return time_stamp 
       */
      inline static time_stamp getSystemTimestamp() { return std::chrono::high_resolution_clock::now(); };

     private:
      inline static auto start = std::chrono::high_resolution_clock::now();
      inline static auto stop = std::chrono::high_resolution_clock::now();
    };
  }
}

#endif