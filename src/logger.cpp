#include "iot/logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace iot {

namespace {

const char* to_text(LogLevel level) {
  switch (level) {
    case LogLevel::kDebug:
      return "DEBUG";
    case LogLevel::kInfo:
      return "INFO";
    case LogLevel::kWarn:
      return "WARN";
    case LogLevel::kError:
      return "ERROR";
  }
  return "UNKNOWN";
}

}  // namespace

Logger::Logger(std::string service_name) : service_name_(std::move(service_name)) {}

void Logger::log(LogLevel level, const std::string& message) {
  const auto now = std::chrono::system_clock::now();
  const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

  std::lock_guard<std::mutex> lock(mutex_);
  std::cout << std::put_time(std::localtime(&now_time), "%F %T") << " [" << service_name_ << "] ["
            << to_text(level) << "] " << message << std::endl;
}

}  // namespace iot
