#include "Logging/Log.h"

using namespace RBC;

std::shared_ptr<spdlog::logger> Log::_coreLogger;
std::shared_ptr<spdlog::logger> Log::_clientLogger;

void Log::init(const std::string &robotName) {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  _coreLogger = spdlog::stderr_color_mt("[Robot Core]");
  _coreLogger->set_level(spdlog::level::trace);

  _clientLogger = spdlog::stderr_color_mt(robotName);
  _clientLogger->set_level(spdlog::level::trace);
}

void Log::setClientName(const std::string &robotName) {
  _clientLogger = spdlog::stderr_color_mt(robotName);
  _clientLogger->set_level(spdlog::level::trace);
}