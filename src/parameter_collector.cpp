#include "iot/parameter_collector.hpp"

#include <array>
#include <cstdio>
#include <fstream>

#include "iot/logger.hpp"

namespace iot {

ParameterCollector::Snapshot ParameterCollector::collect(Logger& logger) const {
  Snapshot out;

  out["machine"] = run_and_capture("uname -m");
  out["kernel"] = run_and_capture("uname -r");
  out["hostname"] = run_and_capture("hostname");
  out["uptime"] = read_first_line("/proc/uptime");
  out["meminfo"] = read_first_line("/proc/meminfo");

  logger.log(LogLevel::kInfo, "collected runtime parameters: " + std::to_string(out.size()));
  return out;
}

std::string ParameterCollector::read_first_line(const std::string& path) {
  std::ifstream in(path);
  if (!in.is_open()) {
    return "N/A";
  }

  std::string line;
  if (!std::getline(in, line) || line.empty()) {
    return "N/A";
  }
  return line;
}

std::string ParameterCollector::run_and_capture(const std::string& cmd) {
  std::array<char, 256> buffer{};
  std::string output;

  FILE* pipe = popen(cmd.c_str(), "r");
  if (pipe == nullptr) {
    return "N/A";
  }

  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
    output.append(buffer.data());
  }
  pclose(pipe);

  while (!output.empty() && (output.back() == '\n' || output.back() == '\r')) {
    output.pop_back();
  }
  return output.empty() ? "N/A" : output;
}

}  // namespace iot
