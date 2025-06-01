#ifndef YKM_APP_VIEWBOX_DEBUG
#define YKM_APP_VIEWBOX_DEBUG

#include <fmt/format.h>

// clang-format off
#ifdef YKM_VIEWBOX_DEBUG
#define ykm_err(...) \
    fmt::println("err: {}\n@{:>8}:{}\n", fmt::format(__VA_ARGS__), __FILE__, __LINE__)

#define ykm_warn(...)\
    fmt::println("warn: {}\n@{:>8}:{}\n", fmt::format(__VA_ARGS__), __FILE__, __LINE__)

#define ykm_log(...)\
    fmt::println("log: {}", fmt::format(__VA_ARGS__))
#else

#define ykm_err(...)
#define ykm_warn(...)
#define ykm_log(...)

#endif

#endif
