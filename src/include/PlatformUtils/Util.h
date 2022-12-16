#ifndef RBC_UTIL_H
#define RBC_UTIL_H

#include <memory>

#ifdef RBC_DEBUG
  #if defined(RBC_PLATFORM_WINDOWS)
    #define RBC_DEBUGBREAK() __debugbreak()
  #elif defined(RBC_PLATFORM_LINUX)
    #include "signal.h"
    #define RBC_DEBUGBREAK() raise(SIGTRAP)
  #else
    #error "Platform does not support debugbreak yet"
  #endif
#else
  #define RBC_DEBUGBREAK()
#endif

#define RBC_EXPAND_MACRO(x) x
#define RBC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#endif