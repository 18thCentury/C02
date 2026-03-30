#include "iot/modules/network_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string NetworkModule::name() const { return "network"; }

bool NetworkModule::initialize(const ConfigStore& config, Logger& logger) {
  const auto health = config.get_or("network_probe", "8.8.8.8");
  logger.log(LogLevel::kInfo, "network init: probe_target=" + health);
  return true;
}

bool NetworkModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "network start: connectivity monitor online");
  return true;
}

void NetworkModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "network stop"); }

}  // namespace iot
