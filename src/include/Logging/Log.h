#ifndef RBC_LOG_H
#define RBC_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace RBC {
  class Log {
   public:
    static void init(const std::string &robotName);
    static void setClientName(const std::string &robotName);
    inline static std::shared_ptr<spdlog::logger> &getCoreLogger() {
      return _coreLogger;
    }

    inline static std::shared_ptr<spdlog::logger> &getClientLogger() {
      return _clientLogger;
    }


   private:
    static std::shared_ptr<spdlog::logger> _coreLogger;
    static std::shared_ptr<spdlog::logger> _clientLogger;
  };
}

#endif