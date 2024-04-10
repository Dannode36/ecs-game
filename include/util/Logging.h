#pragma once
#include "fmt/format.h"
#include <chrono>
#include <string>

#define DEBUG_NONE -1
#define DEBUG_CRTICAL 0
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_INFO 3

#define DEBUG_LEVEL DEBUG_WARNING

const inline std::string getTimeString() {
	return fmt::format("{:%Y-%m-%d %H:%M:%S}", std::chrono::system_clock::now());
}

#if DEBUG_LEVEL >= DEBUG_CRITICAL
	#define LOG_CRITICAL(msg) fmt::print("{} [CRITICAL]: {}", getTimeString(), msg)
#else
	#define LOG_CRITICAL(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_ERROR
	#define LOG_ERROR(msg) fmt::print("{} [ERROR]: {}", getTimeString(), msg)
#else
	#define LOG_ERROR(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_WARNING
	#define LOG_WARNING(msg) fmt::print("{} [WARNING]: {}", getTimeString(), msg)
#else
	#define LOG_WARNING(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_INFO
	#define LOG_INFO(msg) fmt::print("{} [INFO]: {}", getTimeString(), msg)
#else
	#define LOG_INFO(msg)
#endif
