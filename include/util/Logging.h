#pragma once
#include "fmt/format.h"
#include "fmt/chrono.h"
#include <chrono>
#include <string>

#define DEBUG_NONE -1
#define DEBUG_CRTICAL 0
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_INFO 3

#define DEBUG_LEVEL DEBUG_INFO

const inline std::string getTimeString() {
	return fmt::format("{:%H:%M:%S}", std::chrono::round<std::chrono::seconds>(std::chrono::system_clock::now()));
}

#if DEBUG_LEVEL >= DEBUG_CRITICAL
	#define LOG_CRITICAL(msg) fmt::print("[{}] [CRITICAL]: {}\n", getTimeString(), msg)
#else
	#define LOG_CRITICAL(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_ERROR
	#define LOG_ERROR(msg) fmt::print("{} [ERROR]: {}\n", getTimeString(), msg)
#else
	#define LOG_ERROR(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_WARNING
	#define LOG_WARNING(msg) fmt::print("{} [WARNING]: {}\n", getTimeString(), msg)
#else
	#define LOG_WARNING(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_INFO
	#define LOG_INFO(msg) fmt::print("{} [INFO]: {}\n", getTimeString(), msg)
#else
	#define LOG_INFO(msg)
#endif
