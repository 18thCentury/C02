#include "iot/modules/power_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string PowerModule::name() const { return "power"; }

bool PowerModule::initialize(const ConfigStore&, Logger& logger) {
  logger.log(LogLevel::kInfo, "power init: reset hooks armed");
  return true;
}

bool PowerModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "power start: pcie and reboot controls online");
  return true;
}

void PowerModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "power stop"); }

}  // namespace iot
