#pragma once

#include <string>

namespace iot {

class Logger;
class ConfigStore;

class Module {
 public:
  virtual ~Module() = default;
  virtual std::string name() const = 0;
  virtual bool initialize(const ConfigStore& config, Logger& logger) = 0;
  virtual bool start(Logger& logger) = 0;
  virtual void stop(Logger& logger) = 0;
};

}  // namespace iot
