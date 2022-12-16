#ifndef RBC_LOG_H
#define RBC_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace RBC {
  class Log {
   public:
    /**
     * @brief Initialize the logging system with the name of the robot
     * 
     * @param robotName 
     */
    static void init(const std::string &robotName);

    /**
     * @brief Set the Client Name object
     * 
     * @param robotName 
     */
    static void setClientName(const std::string &robotName);

    /**
     * @brief Get the Core Logger object
     * 
     * @return std::shared_ptr<spdlog::logger>& 
     */
    inline static std::shared_ptr<spdlog::logger> &getCoreLogger() {
      return _coreLogger;
    }

    /**
     * @brief Get the Client Logger object
     * 
     * @return std::shared_ptr<spdlog::logger>& 
     */
    inline static std::shared_ptr<spdlog::logger> &getClientLogger() {
      return _clientLogger;
    }


   private:
    static std::shared_ptr<spdlog::logger> _coreLogger;
    static std::shared_ptr<spdlog::logger> _clientLogger;
  };
}

#endif