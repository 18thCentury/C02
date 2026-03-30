#include "iot/modules/serial_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string SerialModule::name() const { return "serial"; }

bool SerialModule::initialize(const ConfigStore&, Logger& logger) {
  logger.log(LogLevel::kInfo, "serial init: loading device identity and auth context");
  return true;
}

bool SerialModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "serial start: command and UART service online");
  return true;
}

void SerialModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "serial stop"); }

}  // namespace iot
