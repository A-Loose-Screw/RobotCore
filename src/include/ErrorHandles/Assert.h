#ifndef RBC_ASSERT_H
#define RBC_ASSERT_H

#include "PlatformUtils/Util.h"
#include "Logging/Print.h"

// filesystem is a bit finicky currently and experimental depending on platform
#if __has_include(<filesystem>)
  #include <filesystem>
  #define rbc_filesystem std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem>
  #define rbc_filesystem std::experimental::filesystem;
#else
  // without filesystem the program will break. So disable asserts
  #define RBC_DISABLE_ASSERTS
#endif

#ifndef RBC_DISABLE_ASSERTS
  #define RBC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { RBC##type##PRINT_ERROR(msg, __VA_ARGS__); RBC_DEBUGBREAK(); } }
  #define RBC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RBC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
  #define RBC_INTERNAL_ASSERT_NO_MSG(type, check) RBC_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RBC_STRINGIFY_MACRO(check), rbc_filesystem::path(__FILE__).filename().string(), __LINE__)

  #define RBC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
  #define RBC_INTERNAL_ASSERT_GET_MACRO(...) RBC_EXPAND_MACRO( RBC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RBC_INTERNAL_ASSERT_WITH_MSG, RBC_INTERNAL_ASSERT_NO_MSG) )

  // Currently accepts at least the condition and one additional parameter (the message) being optional
  #define RBC_ASSERT(...) RBC_EXPAND_MACRO( RBC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
  #define RBC_CORE_ASSERT(...) RBC_EXPAND_MACRO( RBC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
  #define RBC_ASSERT(...)
  #define RBC_CORE_ASSERT(...)
#endif

#endif