#pragma once

#include <string>
#include <unordered_map>

namespace iot {

class Logger;

class ParameterCollector {
 public:
  using Snapshot = std::unordered_map<std::string, std::string>;

  Snapshot collect(Logger& logger) const;

 private:
  static std::string read_first_line(const std::string& path);
  static std::string run_and_capture(const std::string& cmd);
};

}  // namespace iot
