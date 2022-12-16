#ifndef RBC_PRINT_H
#define RBC_PRINT_H

#include <iostream>
#include "Log.h"

#ifndef RBC_DISABLE_LOGGING
  #define RBC_CORE_PRINT(...) ::RBC::print(__VA__ARGS__)
  #define RBC_CORE_PRINT_INFO(...) ::RBC::Log::getCoreLogger()->info(__VA_ARGS__)
  #define RBC_CORE_PRINT_ERROR(...) ::RBC::Log::getCoreLogger()->error(__VA_ARGS__)
  #define RBC_CORE_PRINT_WARN(...) ::RBC::Log::getCoreLogger()->warn(__VA_ARGS__)
  #define RBC_CORE_PRINT_TRACE(...) ::RBC::Log::getCoreLogger()->trace(__VA_ARGS__)

  #define RBC_PRINT(...) ::RBC::print(__VA__ARGS__)
  #define RBC_PRINT_INFO(...) ::RBC::Log::getClientLogger()->info(__VA_ARGS__)
  #define RBC_PRINT_ERROR(...) ::RBC::Log::getClientLogger()->error(__VA_ARGS__)
  #define RBC_PRINT_WARN(...) ::RBC::Log::getClientLogger()->warn(__VA_ARGS__)
  #define RBC_PRINT_TRACE(...) ::RBC::Log::getClientLogger()->trace(__VA_ARGS__)
#else
  #define RBC_CORE_PRINT(...)
  #define RBC_CORE_PRINT_INFO(...)
  #define RBC_CORE_PRINT_ERROR(...)
  #define RBC_CORE_PRINT_WARN(...)
  #define RBC_CORE_PRINT_TRACE(...)

  #define RBC_PRINT(...)
  #define RBC_PRINT_INFO(...)
  #define RBC_PRINT_ERROR(...)
  #define RBC_PRINT_WARN(...)
  #define RBC_PRINT_TRACE(...)
#endif

#endif