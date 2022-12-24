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
       * @brief chrono clocked used by RBC Timer
       * 
       */
      typedef std::chrono::steady_clock clock;

      /**
       * @brief high resolution time_stamp
       * 
       */
      typedef clock::time_point time_stamp;

      /**
       * @brief Duration of time
       * 
       */
      typedef clock::duration duration;

      /**
       * @brief Makes thread sleep until specified timestamp
       * 
       * @param time 
       */
      static void sleepUntil(time_stamp time);

      /**
       * @brief Makes thread sleep for an amount of time
       * 
       * @param time 
       */
      static void sleepFor(duration time);

      /**
       * @brief Makes thread sleep for an amount of time
       * 
       * @param ms 
       */
      static void sleepFor(double ms);

      /**
       * @brief Get the System Timestamp
       * 
       * @return time_stamp 
       */
      inline static time_stamp getSystemTimestamp() { return clock::now(); };

      /**
       * @brief Get the Duration in nanoseconds between the first and second timestamps
       * 
       * @param first 
       * @param second 
       * @return long long 
       */
      static long long getDuration_nano(time_stamp first, time_stamp second);

      /**
       * @brief Get the Duration between the first and second timestamps
       * 
       * @param first 
       * @param second 
       * @return long double 
       */
      static long double getDuration_micro(time_stamp first, time_stamp second);

      /**
       * @brief Get the Duration between the first and second timestamps
       * 
       * @param first 
       * @param second 
       * @return long double 
       */
      static long double getDuration_ms(time_stamp first, time_stamp second);

      /**
       * @brief Get the Duration between the first and second timestamps
       * 
       * @param first 
       * @param second 
       * @return long double 
       */
      static long double getDuration_s(time_stamp first, time_stamp second);


     private:
      inline static auto start = clock::now();
      inline static auto stop = clock::now();
    };
  }
}

#endif