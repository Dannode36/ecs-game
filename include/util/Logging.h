#pragma once
#include "fmt/format.h"
#include "fmt/chrono.h"
#include <chrono>
#include <string>
#include <fstream>
#include "iostream"

#define DEBUG_NONE -1
#define DEBUG_CRTICAL 0
#define DEBUG_ERROR 1
#define DEBUG_WARNING 2
#define DEBUG_INFO 3

#define DEBUG_LEVEL DEBUG_INFO

#define LOG(msg) std::cout << msg; \
	std::ofstream log("logfile.txt", std::ios_base::app | std::ios_base::out); \
	log << msg;

const inline std::string getTimeString() {
	return fmt::format("{:%H:%M:%S}", std::chrono::round<std::chrono::seconds>(std::chrono::system_clock::now()));
}

#if DEBUG_LEVEL >= DEBUG_CRITICAL
	#define LOG_CRITICAL(msg) LOG(fmt::format("[{}] [CRITICAL]: {}\n", getTimeString(), msg))
#else
	#define LOG_CRITICAL(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_ERROR
	#define LOG_ERROR(msg) LOG(fmt::format("{} [ERROR]: {}\n", getTimeString(), msg))
#else
	#define LOG_ERROR(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_WARNING
	#define LOG_WARNING(msg) LOG(fmt::format("{} [WARNING]: {}\n", getTimeString(), msg))
#else
	#define LOG_WARNING(msg)
#endif

#if DEBUG_LEVEL >= DEBUG_INFO
	#define LOG_INFO(msg) LOG(fmt::format("{} [INFO]: {}\n", getTimeString(), msg))
#else
	#define LOG_INFO(msg)
#endif
