#pragma once

#include <mutex>
#include <string>

namespace iot {

enum class LogLevel { kDebug, kInfo, kWarn, kError };

class Logger {
 public:
  explicit Logger(std::string service_name);
  void log(LogLevel level, const std::string& message);

 private:
  std::string service_name_;
  std::mutex mutex_;
};

}  // namespace iot
