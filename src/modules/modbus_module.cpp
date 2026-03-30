#include "iot/modules/modbus_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string ModbusModule::name() const { return "modbus"; }

bool ModbusModule::initialize(const ConfigStore& config, Logger& logger) {
  const auto port = config.get_or("modbus_port", "502");
  logger.log(LogLevel::kInfo, "modbus init: tcp_port=" + port);
  return true;
}

bool ModbusModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "modbus start: slave service online");
  return true;
}

void ModbusModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "modbus stop"); }

}  // namespace iot
