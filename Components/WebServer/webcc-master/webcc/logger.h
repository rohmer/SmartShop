#ifndef WEBCC_LOGGER_H_
#define WEBCC_LOGGER_H_

// This file was generated from "config.h.in" by CMake.
#include "webcc/config.h"

#include <cstring>  // for strrchr()
#include <filesystem>
#include <string>

// Log levels.
// VERB is similar to DEBUG commonly used by other projects.
// USER is for the users who want to log their own logs but don't want any
// VERB or INFO.
#define WEBCC_VERB 0
#define WEBCC_INFO 1
#define WEBCC_USER 2
#define WEBCC_WARN 3
#define WEBCC_ERRO 4
#define WEBCC_NONE 5

// Default log level.
#ifndef WEBCC_LOG_LEVEL
#define WEBCC_LOG_LEVEL WEBCC_USER
#endif

#define WEBCC_LOG_FILE_NAME "webcc.log"

namespace webcc {

enum LogMode {
  LOG_FILE        = 1,  // Log to file.
  LOG_CONSOLE     = 2,  // Log to console.
  LOG_FLUSH       = 4,  // Flush on each log.
  LOG_OVERWRITE   = 8,  // Overwrite any existing log file.
};

// Commonly used modes.
const int LOG_CONSOLE_FILE_APPEND = LOG_CONSOLE | LOG_FILE;
const int LOG_CONSOLE_FILE_OVERWRITE = LOG_CONSOLE | LOG_FILE | LOG_OVERWRITE;
const int LOG_FILE_OVERWRITE = LOG_FILE | LOG_OVERWRITE;
const int LOG_FILE_FLUSH_OVERWRITE = LOG_FILE | LOG_FLUSH | LOG_OVERWRITE;

// Initialize logger.
// If |dir| is empty, log file will be generated in current directory.
void LogInit(const std::filesystem::path& dir, int modes);

void Log(int level, const char* file, int line, const char* format, ...);

}  // namespace webcc

#ifdef _WIN32

// See: https://stackoverflow.com/a/8488201
// ISSUE: The last path separator of __FILE__ in a header file becomes "/"
//        instead of "\". The result is that __FILENAME__ will contain a
//        prefix of "webcc/". So don't log from a header file!
#define __FILENAME__ std::strrchr("\\" __FILE__, '\\') + 1

#else

#define __FILENAME__ std::strrchr("/" __FILE__, '/') + 1

#endif  // _WIN32

#if WEBCC_LOG_LEVEL <= WEBCC_VERB
#define LOG_VERB(format, ...) \
  webcc::Log(WEBCC_VERB, __FILENAME__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG_VERB(format, ...)
#endif

#if WEBCC_LOG_LEVEL <= WEBCC_INFO
#define LOG_INFO(format, ...) \
  webcc::Log(WEBCC_INFO, __FILENAME__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG_INFO(format, ...)
#endif

#if WEBCC_LOG_LEVEL <= WEBCC_USER
#define LOG_USER(format, ...) \
  webcc::Log(WEBCC_USER, __FILENAME__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG_USER(format, ...)
#endif

#if WEBCC_LOG_LEVEL <= WEBCC_WARN
#define LOG_WARN(format, ...) \
  webcc::Log(WEBCC_WARN, __FILENAME__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG_WARN(format, ...)
#endif

#if WEBCC_LOG_LEVEL <= WEBCC_ERRO
#define LOG_ERRO(format, ...) \
  webcc::Log(WEBCC_ERRO, __FILENAME__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG_ERRO(format, ...)
#endif

#if WEBCC_LOG_LEVEL < WEBCC_NONE
#define WEBCC_LOG_INIT(dir, modes) webcc::LogInit(dir, modes);
#else
#define WEBCC_LOG_INIT(dir, modes)
#endif

#endif  // WEBCC_LOGGER_H_
