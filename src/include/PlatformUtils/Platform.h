#ifndef RBC_PLATFORM_DETECTION_H
#define RBC_PLATFORM_DETECTION_H

/**
 * @brief Detect platform
 * 
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #define RBC_PLATFORM_WINDOWS

  #ifdef _WIN64
    #define RBC_PLATFORM_WINDOWS_X86_64
  #else
    #define RBC_PLATFORM_WINDOWS_X86
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #include <TargetConditionals.h>
  #define RBC_PLATFORM_UNIX

  #if TARGET_IPHONE_SIMULATOR
    // iOS, tvOS, or watchOS Simulator
  #elif TARGET_OS_MACCATALYST
    // Mac's Catalyst (ports iOS API into Mac, like UIKit).
  #elif TARGET_OS_IPHONE
    #define RBC_PLATFORM_IOS
  #elif TARGET_OS_MAC
    #define RBC_PLATFORM_MACOS
  #else
    #error "Unknown Apple platform"
  #endif
#elif __linux__
  #define RBC_PLATFORM_LINUX
  #define RBC_PLATFORM_UNIX
#elif __unix__ // all unices not caught above
  #define RBC_PLATFORM_UNIX

#elif defined(_POSIX_VERSION)
  #define RBC_PLATFORM_POSIX
#else
  #error "Unknown compiler"
#endif

/**
 * @brief Detect compiler
 * 
 */
#if defined(__clang__)
  #define RBC_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
  #define RBC_GCC
#elif defined(_MSC_VER)
  #define RBC_MSC
#endif

#endif